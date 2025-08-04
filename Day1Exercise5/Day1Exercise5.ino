#include <Arduino.h>

const int redLedPin = 4;
const int blueLedPin = 5;
const int cycles = 3;
const int delayTime = 50;

void setup() {
    pinMode(redLedPin, OUTPUT);
    pinMode(blueLedPin, OUTPUT);
}

void loop() {
    // Blink red
    blink(redLedPin, cycles);
    // Switching delay
    delay(200);
    // Blink blue
    blink(blueLedPin, cycles);
}

void blink(int ledPin, int times) {
    for (int i = 0; i < times; i++) {
        digitalWrite(ledPin, HIGH);
        delay(delayTime);
        digitalWrite(ledPin, LOW);
        delay(delayTime);
    }
}
