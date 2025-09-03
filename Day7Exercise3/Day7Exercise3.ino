#include<Arduino.h>

/** Constants **/
const unsigned int DATA_PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const unsigned int LED_SSD_GND_PINS[2] = {14, 15};
const unsigned int LED_GND_INDEX = 0;
const unsigned int SSD_GND_INDEX = 1;
const unsigned int PROG_DELAY = 5;
const unsigned int SWITCHING_PINS[4] = {16, 17, 18, 19};

/* SSD Constants */
const unsigned int DIGIT_MAP[10] = {
    0x3f,
    0x06,
    0x5b,
    0x4f,
    0x66,
    0x6d,
    0x7d,
    0x07,
    0x7f,
    0x6f
};

/** Variables **/
int ADCVal = 0;
float Varef = 5;

void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
}

void loop() {
    ADCVal = analogRead(A0);
    float sigVolt = (Varef/1024) * ADCVal;

    // Printing analog voltage
    Serial.print("Voltage: ");
    Serial.print((int)sigVolt);
    Serial.println(" V");

    delay(PROG_DELAY);
}
