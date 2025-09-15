#include<Arduino.h>

const char BTN = 2;
const char ENA = 3; 
const char IN1 = 4;
const char IN2 = 5;

volatile bool in1_val = true;
volatile bool in2_val = false;
int adc_val = 0;
int pwm_val = 0;

void setup() {
    Serial.begin(9600);

    pinMode(BTN, INPUT_PULLUP);
    pinMode(A0, INPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(BTN), switchDirection, FALLING);
}

void loop() {
    digitalWrite(IN1, in1_val);
    digitalWrite(IN2, in2_val);

    adc_val = analogRead(A0);
    pwm_val = adc_val/4;

    Serial.print(adc_val);
    Serial.print("->");
    Serial.println(pwm_val);

    analogWrite(ENA, pwm_val);

    delay(5);
}

void switchDirection() {
    in1_val = !in1_val;
    in2_val = !in2_val;
}
