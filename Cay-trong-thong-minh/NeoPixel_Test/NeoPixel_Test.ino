#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN    2
#define NUM_PIXELS      12
#define BRIGHTNESS      150

Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("NeoPixel Test Starting...");

    pixels.begin();
    pixels.setBrightness(BRIGHTNESS);
    pixels.clear();
    pixels.show();

    Serial.print("Pin: GPIO ");
    Serial.print(NEOPIXEL_PIN);
    Serial.print(", LEDs: ");
    Serial.println(NUM_PIXELS);
}

void loop() {
    // Test 1: All WHITE
    Serial.println("WHITE");
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    }
    pixels.show();
    delay(3000);

    // Test 2: All RED
    Serial.println("RED");
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
    pixels.show();
    delay(3000);

    // Test 3: All GREEN
    Serial.println("GREEN");
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    }
    pixels.show();
    delay(3000);

    // Test 4: All BLUE
    Serial.println("BLUE");
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    }
    pixels.show();
    delay(3000);

    // Test 5: One by one
    Serial.println("ONE BY ONE");
    pixels.clear();
    for (int i = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 255));
        pixels.show();
        delay(500);
        pixels.setPixelColor(i, 0);
    }
    pixels.clear();
    pixels.show();
    delay(2000);
}
