#include<Arduino.h>

const unsigned int PROGRAM_DELAY = 50;
const unsigned int LED_PATTERN_MULTIPLIER = 2;

void setup() {
    for (int i = 2; i < 14; i++) {
        pinMode(i, OUTPUT);
    }
}

void loop() {
    
    delay(PROGRAM_DELAY);
}
