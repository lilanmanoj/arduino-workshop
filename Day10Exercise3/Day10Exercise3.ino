#include <Arduino.h>

const char enA = 3; 
const char in1 = 4;
const char in2 = 5;

char pwm_val = 20;

void setup() {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enA, OUTPUT);
}

void loop() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, pwm_val);

    delay(1000);
}
