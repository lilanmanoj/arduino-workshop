#include<Arduino.h>

unsigned int LED_GND_INDEX = 0;
unsigned int SSD_GND_INDEX = 1;

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

void clearData(unsigned int PINS[]) {
    for (int x = 0; x < sizeof(PINS)/sizeof(PINS[0]) ; x++) {
        digitalWrite(PINS[x], LOW);
    }
}

void clearSelection(unsigned int PINS[]) {
    for (int x = 0; x < sizeof(PINS)/sizeof(PINS[0]) ; x++) {
        digitalWrite(PINS[x], LOW);
    }
}

void SSDSelect(unsigned int PINS[], unsigned int idx) {
    clearSelection(PINS);
    digitalWrite(PINS[idx], HIGH);
}

void SSDWrite(unsigned int GND_PINS[], unsigned int PINS[], unsigned int digit) {
    clearData(PINS);
    digitalWrite(GND_PINS[LED_GND_INDEX], HIGH);
    digitalWrite(GND_PINS[SSD_GND_INDEX], LOW);

    unsigned int value = DIGIT_MAP[digit];

    for (int x = 0; x < 8; x++) {
        unsigned int mask = 1<<x;
        unsigned int check = value & mask;

        if (check == mask) {
            digitalWrite(PINS[x], HIGH);
        }
    }
}
