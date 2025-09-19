#include<Arduino.h>

const unsigned int FIXED_RESISTANCE = 1000;
const uint8_t APIN = 18; 
int adc_val = 0;
float voltage = 0;
float resistance = 0;

void setup() {
    Serial.begin(9600);
    pinMode(APIN, INPUT);
}

void loop() {
    adc_val = analogRead(APIN);
    voltage = adc_val * (5.0/1023);
    resistance = voltage * FIXED_RESISTANCE / (5.0 - voltage);

    Serial.print("Voltage: ");
    Serial.println(voltage);
    Serial.print("Resistor: ");
    Serial.println(resistance);

    delay(500);
}
