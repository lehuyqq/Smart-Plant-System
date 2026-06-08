#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <XPT2046_Touchscreen.h>
#include <WiFi.h>
#include <time.h>
#include <DHT.h>

#if __has_include("secrets.h")
#include "secrets.h"
#else
#error "Create secrets.h from secrets.example.h and set WIFI_SSID/WIFI_PASSWORD before compiling."
#endif

// NTP
const char *NTP_SERVER   = "pool.ntp.org";
const long GMT_OFFSET_SEC = 7 * 3600;  // GMT+7 Vietnam
const int  DST_OFFSET_SEC = 0;

// ========== SENSOR PINS ==========
#define DHT_PIN       27
#define DHT_TYPE      DHT11   // Try DHT11 first, change to DHT22 if needed
#define RAIN_PIN      34   // Digital rain sensor
#define SOIL_PIN      35   // Analog soil moisture sensor

// Soil moisture calibration (raw ADC -> percentage)
#define SOIL_DRY      4095
#define SOIL_WET      1200

// ========== RELAY PINS ==========
#define RELAY_LIGHT   15
#define RELAY_PUMP    2

// ========== OBJECTS ==========
TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen ts(21);
DHT dht(DHT_PIN, DHT_TYPE);

// ========== LVGL BUFFER ==========
#define LV_HOR_RES_MAX 320
#define LV_VER_RES_MAX 240
#define DISP_BUF_SIZE (LV_HOR_RES_MAX * LV_VER_RES_MAX / 5)

lv_color_t *buf_1;
lv_display_t *disp;

// Touch calibration
const uint16_t RAW_MIN_X = 429;
const uint16_t RAW_MAX_X = 3593;
const uint16_t RAW_MIN_Y = 1905;
const uint16_t RAW_MAX_Y = 3345;
const bool INVERT_X = false;
const bool INVERT_Y = true;

// ========== EEZ STUDIO FILES ==========
#include "ui.h"
#include "screens.h"
#include "vars.h"
#include "images.h"

// Forward declaration
void disp_flush(lv_display_t *display, const lv_area_t *area, unsigned char *data);

// ========== TIMING ==========
static unsigned long lastSensorMs = 0;
static unsigned long lastDashboardMs = 0;
const unsigned long SENSOR_INTERVAL_MS = 5000;
const unsigned long DASH_INTERVAL_MS   = 500;

// ========== NTP TIME ==========
static bool ntpSynced = false;

void syncTime() {
    configTime(GMT_OFFSET_SEC, DST_OFFSET_SEC, NTP_SERVER);
    struct tm timeinfo;
    if (getLocalTime(&timeinfo, 5000)) {
        ntpSynced = true;
        Serial.printf("NTP synced: %02d:%02d %02d/%02d/%d\n",
            timeinfo.tm_hour, timeinfo.tm_min,
            timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
    } else {
        Serial.println("NTP sync failed");
    }
}

// ========== TOUCH ==========
static inline int32_t fmap_clamped(int32_t val, int32_t in_min, int32_t in_max,
                                   int32_t out_min, int32_t out_max) {
    if (in_max == in_min) return out_min;
    if (in_min < in_max) {
        long mapped = (long)(val - in_min) * (out_max - out_min) / (long)(in_max - in_min) + out_min;
        if (mapped < out_min) return out_min;
        if (mapped > out_max) return out_max;
        return (int32_t)mapped;
    } else {
        long mapped = (long)(in_min - val) * (out_max - out_min) / (long)(in_min - in_max) + out_min;
        if (mapped < out_min) return out_min;
        if (mapped > out_max) return out_max;
        return (int32_t)mapped;
    }
}

void touch_read(lv_indev_t *indev_driver, lv_indev_data_t *data) {
    if (!ts.touched()) {
        data->state = LV_INDEV_STATE_RELEASED;
        return;
    }

    TS_Point p = ts.getPoint();
    int32_t mx = fmap_clamped(p.x, RAW_MIN_X, RAW_MAX_X, 0, tft.width());
    int32_t my = fmap_clamped(p.y, RAW_MIN_Y, RAW_MAX_Y, 0, tft.height());

    if (INVERT_X) mx = tft.width() - mx;
    if (INVERT_Y) my = tft.height() - my;

    if (mx < 0) mx = 0;
    if (mx > tft.width()) mx = tft.width();
    if (my < 0) my = 0;
    if (my > tft.height()) my = tft.height();

    data->state = LV_INDEV_STATE_PRESSED;
    data->point.x = (lv_coord_t)mx;
    data->point.y = (lv_coord_t)my;
}

// ========== UI INIT ==========
void setup_ui(void) {
    ui_init();
    if (objects.main) {
        lv_screen_load(objects.main);
    }
}

// ========== SWITCH CALLBACKS ==========
static void light_switch_cb(lv_event_t *e) {
    bool on = lv_obj_has_state(objects.light, LV_STATE_CHECKED);
    digitalWrite(RELAY_LIGHT, on ? HIGH : LOW);
    Serial.printf("Light: %s\n", on ? "ON" : "OFF");
}

static void pump_switch_cb(lv_event_t *e) {
    bool on = lv_obj_has_state(objects.pump, LV_STATE_CHECKED);
    digitalWrite(RELAY_PUMP, on ? HIGH : LOW);
    Serial.printf("Pump: %s\n", on ? "ON" : "OFF");
}

// ========== READ SENSORS ==========
void readSensors() {
    // DHT - read with retry
    float t = NAN, h = NAN;
    for (int i = 0; i < 3; i++) {
        t = dht.readTemperature();
        h = dht.readHumidity();
        if (!isnan(t) && !isnan(h)) break;
        delay(200);
    }

    if (!isnan(t) && !isnan(h)) {
        set_var_temperture_value((int32_t)round(t));
        set_var_humidity_value((int32_t)round(h));
        Serial.printf("DHT: %.1fC %.1f%%\n", t, h);
    } else {
        Serial.println("DHT: FAILED");
    }

    // Soil moisture (analog A0)
    int soilRaw = analogRead(SOIL_PIN);
    int soilPercent = map(soilRaw, SOIL_DRY, SOIL_WET, 0, 100);
    soilPercent = constrain(soilPercent, 0, 100);
    set_var_air_quality_value(soilPercent);
    Serial.printf("Soil: raw=%d percent=%d%%\n", soilRaw, soilPercent);

    // Rain sensor (analog A0)
    int rainRaw = analogRead(RAIN_PIN);
    int rainPercent = map(rainRaw, 4095, 0, 0, 100);
    rainPercent = constrain(rainPercent, 0, 100);
    set_var_rain_percent(rainPercent);
    Serial.printf("Rain: raw=%d percent=%d%%\n", rainRaw, rainPercent);
}

// ========== UPDATE TIME ==========
void updateTime() {
    if (!ntpSynced) return;

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo, 100)) return;

    set_var_time_hour(timeinfo.tm_hour);
    set_var_time_minute(timeinfo.tm_min);
    set_var_date(timeinfo.tm_mday);
    set_var_dayof_week_var((DayOfWeek)timeinfo.tm_wday);

    static const char *months[] = {
        "01","02","03","04","05","06",
        "07","08","09","10","11","12"
    };
    if (timeinfo.tm_mon >= 0 && timeinfo.tm_mon < 12) {
        set_var_month(months[timeinfo.tm_mon]);
    }
}

// ========== DASHBOARD UPDATE ==========
void update_dashboard() {
    updateTime();
    char buf[64];

    // Time
    if (objects.hour) {
        snprintf(buf, sizeof(buf), "%02ld", (long)get_var_time_hour());
        lv_label_set_text(objects.hour, buf);
    }
    if (objects.minute) {
        snprintf(buf, sizeof(buf), "%02ld", (long)get_var_time_minute());
        lv_label_set_text(objects.minute, buf);
    }

    // Day of week
    if (objects.thu) {
        int dow = (int)get_var_dayof_week_var();
        static const char *dow_names[] = {"CN","T2","T3","T4","T5","T6","T7"};
        if (dow >= 0 && dow < 7) {
            lv_label_set_text(objects.thu, dow_names[dow]);
        }
    }

    // Day
    if (objects.day) {
        snprintf(buf, sizeof(buf), "%02ld", (long)get_var_date());
        lv_label_set_text(objects.day, buf);
    }

    // Month
    if (objects.month) {
        lv_label_set_text(objects.month, get_var_month());
    }

    // Temperature
    if (objects.temp) {
        int32_t tempVal = get_var_temperture_value();
        snprintf(buf, sizeof(buf), "%ld", (long)tempVal);
        lv_label_set_text(objects.temp, buf);
        Serial.printf("Display temp: %ld\n", (long)tempVal);
    }

    // Update arc based on temperature
    if (objects.obj1) {
        int32_t tempVal = get_var_temperture_value();
        if (tempVal < 0) tempVal = 0;
        if (tempVal > 100) tempVal = 100;
        lv_arc_set_value(objects.obj1, tempVal);
    }

    // Soil moisture status
    if (objects.stats_soil) {
        int32_t soil = get_var_air_quality_value();
        const char *status = "N/A";
        if (soil >= 80) status = "Good";
        else if (soil >= 50) status = "Fine";
        else status = "Low";
        lv_label_set_text(objects.stats_soil, status);
    }

    // Soil moisture number
    if (objects.stats_soil_number) {
        snprintf(buf, sizeof(buf), "%ld%%", (long)get_var_air_quality_value());
        lv_label_set_text(objects.stats_soil_number, buf);
    }

    // Rain bar + status + icon
    int32_t rainPct = get_var_rain_percent();
    if (objects.rain_bar) {
        lv_bar_set_value(objects.rain_bar, rainPct, LV_ANIM_ON);
    }
    if (objects.rain_stats) {
        if (rainPct >= 30) {
            lv_label_set_text(objects.rain_stats, "Rain");
        } else {
            lv_label_set_text(objects.rain_stats, "Sun");
        }
    }
    if (objects.weather) {
        if (rainPct >= 30) {
            lv_image_set_src(objects.weather, &img_rain);
        } else {
            lv_image_set_src(objects.weather, &img_sun);
        }
    }
}

// ========== SETUP ==========
void setup() {
    Serial.begin(115200);
    delay(1000);

    // Backlight
    pinMode(32, OUTPUT);
    digitalWrite(32, HIGH);

    // Relays
    pinMode(RELAY_LIGHT, OUTPUT);
    pinMode(RELAY_PUMP, OUTPUT);
    digitalWrite(RELAY_LIGHT, LOW);
    digitalWrite(RELAY_PUMP, LOW);

    // TFT init
    tft.init();
    tft.setRotation(3);
    tft.setSwapBytes(true);
    tft.fillScreen(TFT_BLACK);

    // Touch init
    ts.begin();
    ts.setRotation(3);

    // DHT sensor
    pinMode(DHT_PIN, INPUT_PULLUP);  // Enable internal pull-up
    dht.begin();
    delay(3000);  // DHT needs time to stabilize
    Serial.println("DHT initialized on GPIO 27");

    // Test read
    float testT = dht.readTemperature();
    if (!isnan(testT)) {
        Serial.printf("DHT test read: %.1fC OK\n", testT);
    } else {
        Serial.println("DHT test read: FAILED - check wiring!");
        Serial.println("  DATA -> GPIO 27, VCC -> 3.3V, GND -> GND");
        Serial.println("  Pull-up 4.7k between DATA and VCC");
    }

    // Rain + Soil pins (both analog A0)
    pinMode(RAIN_PIN, INPUT);
    pinMode(SOIL_PIN, INPUT);

    // WiFi connect
    Serial.printf("Connecting to %s", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    unsigned long wifiStart = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - wifiStart < 15000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("\nWiFi OK: %s\n", WiFi.localIP().toString().c_str());
        syncTime();
    } else {
        Serial.println("\nWiFi failed - using fallback time");
        set_var_time_hour(12);
        set_var_time_minute(0);
        set_var_date(14);
        set_var_month("05");
    }

    // LVGL init
    lv_init();

    buf_1 = (lv_color_t *)malloc(DISP_BUF_SIZE * sizeof(lv_color_t));
    if (!buf_1) {
        while (1) delay(100);
    }

    disp = lv_display_create(tft.width(), tft.height());
    lv_display_set_buffers(disp, buf_1, NULL, DISP_BUF_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(disp, disp_flush);

    lv_indev_t *indev_touch = lv_indev_create();
    lv_indev_set_type(indev_touch, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touch, touch_read);

    setup_ui();

    // Set arc range for temperature (0-100)
    if (objects.obj1) {
        lv_arc_set_range(objects.obj1, 0, 100);
    }

    // Switch event callbacks
    if (objects.light) {
        lv_obj_add_event_cb(objects.light, light_switch_cb, LV_EVENT_VALUE_CHANGED, NULL);
    }
    if (objects.pump) {
        lv_obj_add_event_cb(objects.pump, pump_switch_cb, LV_EVENT_VALUE_CHANGED, NULL);
    }

    // Initial sensor read
    readSensors();

    // Set default values if sensor failed
    if (get_var_temperture_value() == 0) {
        set_var_temperture_value(25);
        Serial.println("Using default temp: 25");
    }
}

// ========== LOOP ==========
void loop() {
    lv_tick_inc(1);
    lv_task_handler();

    unsigned long now = millis();

    if (now - lastSensorMs >= SENSOR_INTERVAL_MS) {
        lastSensorMs = now;
        readSensors();
    }

    if (now - lastDashboardMs >= DASH_INTERVAL_MS) {
        lastDashboardMs = now;
        update_dashboard();
    }

    delay(1);
}
