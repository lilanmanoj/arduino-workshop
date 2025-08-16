#include<Arduino.h>

const unsigned int DATA_PINS[8] = {15, 14, 7, 6, 5, 4, 3, 2};
const unsigned int LED_GND_PIN = 12;
const unsigned int SSD_GND_PIN = 13;

void setup() {
    for (int x = 0; x < sizeof(DATA_PINS)/sizeof(DATA_PINS[0]); x++) {
        pinMode(DATA_PINS[x], OUTPUT);
    }

    pinMode(LED_GND_PIN, OUTPUT);
    pinMode(SSD_GND_PIN, OUTPUT);

    digitalWrite(LED_GND_PIN, LOW);
    digitalWrite(SSD_GND_PIN, HIGH);

}

void loop() {
    unsigned char val = 11;

    displayValue(val);
}

void displayValue(unsigned char num) {
    for (int x = 0; x < sizeof(DATA_PINS)/sizeof(DATA_PINS[0]); x++) {
        digitalWrite(DATA_PINS[x], num & (1<<x));
    }
}
