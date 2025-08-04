#include <Arduino.h>

int LED_PIN = 4;

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_PIN, LOW);  // Turn the LED off
    delay(278);                   // Wait for 278 milliseconds
    digitalWrite(LED_PIN, HIGH);   // Turn the LED on
    delay(555);                   // Wait for 555 milliseconds
}
