#include <Arduino.h>
#include <Servo.h>

Servo myservo;

const char SERVO_PIN = 9;

void setup() {
    myservo.attach(SERVO_PIN, 500, 2400);
}

void loop() {
    myservo.write(0);
    delay(1000);
    myservo.write(90);
    delay(1000);
    myservo.write(135);
    delay(1000);
    myservo.write(180);
    delay(1000);
}
