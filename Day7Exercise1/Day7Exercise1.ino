#include<Arduino.h>

int ADCVal = 0;
float Varef = 5;

void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
}

void loop() {
    ADCVal = analogRead(A0);
    float sigVolt = (Varef/1024) * ADCVal;

    // Printing digital representation level
    // Serial.println(ADCVal);

    // Printing analog voltage
    Serial.print("Voltage: ");
    Serial.print(sigVolt);
    Serial.println(" V");

    delay(500);
}
