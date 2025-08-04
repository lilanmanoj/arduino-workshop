#include <Arduino.h>

int LED_PIN = 4;

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_PIN, HIGH);  // Turn the LED on
    delay(500);                   // Wait for a second
    digitalWrite(LED_PIN, LOW);   // Turn the LED off
    delay(500);                   // Wait for a second
}
