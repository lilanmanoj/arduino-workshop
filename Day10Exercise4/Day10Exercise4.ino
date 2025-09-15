#include<Arduino.h>

const char ENA = 3; 
const char IN1 = 4;
const char IN2 = 5;

int adc_val = 0;
int pwm_val = 0;

void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);
}

void loop() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    adc_val = analogRead(A0);
    pwm_val = adc_val/4;

    Serial.print(adc_val);
    Serial.print("->");
    Serial.println(pwm_val);

    analogWrite(ENA, pwm_val);

    delay(5);
}
