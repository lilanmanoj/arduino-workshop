#include<Arduino.h>

const unsigned int LED_PIN = 3;
const unsigned int PROG_DELAY = 5;

int ADCVal = 0;
int PWMVal = 0;

void setup() {
    // Uncomment for debug
    // Serial.begin(9600);

    pinMode(A0, INPUT);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    ADCVal = analogRead(A0);
    PWMVal = ADCVal/4;

    // Uncomment for debug
    // Serial.println(PWMVal);

    analogWrite(LED_PIN, PWMVal);

    delay(PROG_DELAY);
}
