#include<Arduino.h>

const int PROG_DELAY = 5;
const uint8_t LED_GND = 11;
const uint8_t SSD_GND = 12;
const uint8_t SSDS[4] = {16, 17, 18, 19};
const uint8_t SEGMENTS[8] = {2, 3, 4, 5, 6, 7, 8, 9}; 
const uint8_t SW1 = 10;

const uint8_t CHAR_MAP[4] = {
    0x4c,
    0x54,
    0x58,
    0x1c
};

unsigned int dl = 500;

void setup() {
    pinMode(SW1, INPUT);
    pinMode(LED_GND, OUTPUT);
    pinMode(SSD_GND, OUTPUT);

    for (uint8_t i = 0; i < sizeof(SSDS)/sizeof(SSDS[0]); i++) {
        pinMode(SSDS[i], OUTPUT);
    }

    for (uint8_t i = 0; i < sizeof(SEGMENTS)/sizeof(SEGMENTS[0]); i++) {
        pinMode(SEGMENTS[i], OUTPUT);
    }

    digitalWrite(LED_GND, HIGH);
    digitalWrite(SSD_GND, LOW);
}

void loop() {
    writeDigit(0, 0);
    delay(PROG_DELAY);
    writeDigit(1, 1);
    delay(PROG_DELAY);
    writeDigit(2, 2);
    delay(PROG_DELAY);
    writeDigit(3, 3);
    delay(PROG_DELAY);
}

void writeDigit(uint8_t ssd, uint8_t c) {
    uint8_t i = 0;

    for (i = 0; i < sizeof(SSDS)/sizeof(SSDS[0]); i++) {
        digitalWrite(SSDS[i], ssd == i);
    }

    for (i = 0; i < sizeof(SEGMENTS)/sizeof(SEGMENTS[0]); i++) {
        digitalWrite(SEGMENTS[i], CHAR_MAP[c] & 1 << i);
    }
}
