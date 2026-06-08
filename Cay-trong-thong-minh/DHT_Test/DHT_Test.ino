#include <DHT.h>

// Change pin number to match your wiring
// Arduino Uno: any digital pin (2, 3, 4, etc.)
// Arduino Mega: any digital pin
#define DHT_PIN   2    // Connect DHT21 DATA to this pin
#define DHT_TYPE  DHT21

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    Serial.begin(9600);
    delay(2000);
    Serial.println("=== DHT21 TEST ===");
    Serial.print("Pin: D");
    Serial.println(DHT_PIN);

    dht.begin();
    delay(3000);

    Serial.println("Ready. Reading every 2s...\n");
}

void loop() {
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (isnan(t) || isnan(h)) {
        Serial.println("READ FAILED!");
        Serial.println("Check wiring:");
        Serial.println("  VCC  -> 5V");
        Serial.println("  DATA -> D2");
        Serial.println("  GND  -> GND");
        Serial.println("  4.7k pull-up DATA->VCC");
        Serial.println();
    } else {
        Serial.print("Temp: ");
        Serial.print(t);
        Serial.println(" C");
        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.println(" %");
        Serial.println("---");
    }

    delay(2000);
}
