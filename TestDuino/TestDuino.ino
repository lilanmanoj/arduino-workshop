#include <Arduino.h>

void setup() {
    // Initiate Serial communication
    // at a baud rate of 9600
    Serial.begin(9600);
    // Make LEd_BUILTIN an output pin
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    // Blink the LED_BUILTIN every second
    blink();
}

void blink() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}