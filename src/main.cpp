#include <Arduino.h>

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.println("Blink!");
    delay(1000);
    Serial.println("Off!");
    delay(1000);
}
