#include <Arduino.h>
#include <Servo.h>

Servo myservo;

const char SERVO_PIN = 9;
const char POT_PIN = A0;
unsigned int val = 0;

void setup() {
    pinMode(SERVO_PIN, INPUT);
    myservo.attach(SERVO_PIN, 500, 2400);
}

void loop() {
    val = analogRead(POT_PIN);
    val = map(val, 0, 1023, 0, 180);
    myserco.write(val);
    delay(15);
}
