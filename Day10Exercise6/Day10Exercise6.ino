#include <Arduino.h>

const char SERVO_PIN = 9;

void setup() {
    pinMode(SERVO_PIN, OUTPUT);
}

void loop() {
    digitalWrite(SERVO_PIN, HIGH);
    delayMicroseconds(1450);
    digitalWrite(SERVO_PIN, LOW);
    delayMicroseconds(20000 - 1450);

    // digitalWrite(SERVO_PIN, HIGH);
    // delayMicroseconds(2000);
    // digitalWrite(SERVO_PIN, LOW);
    // delayMicroseconds(20000 - 2000);
}
