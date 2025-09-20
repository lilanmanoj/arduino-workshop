#include<Arduino.h>

const uint8_t LEDS[4] = {2,3,4,5};
const uint8_t LED_GND = 11;

void setup() {
    for (uint8_t i = 0; i < sizeof(LEDS)/sizeof(LEDS[0]); i++) {
        pinMode(LEDS[i], OUTPUT);
    }

    pinMode(LED_GND, OUTPUT);
    digitalWrite(LED_GND, LOW);
}

void loop() {
    uint8_t i = 0;

    for (i = 0; i < 4; i++) {
        digitalWrite(LEDS[0], HIGH);
        digitalWrite(LEDS[1], HIGH);
        delay(500);
        digitalWrite(LEDS[0], LOW);
        digitalWrite(LEDS[1], LOW);
        delay(500);
    }
    
    delay(1000);

    for (i = 0; i < 3; i++) {
        digitalWrite(LEDS[2], HIGH);
        digitalWrite(LEDS[3], HIGH);
        delay(500);
        digitalWrite(LEDS[2], LOW);
        digitalWrite(LEDS[3], LOW);
        delay(500);
    }

    delay(1000);
}
