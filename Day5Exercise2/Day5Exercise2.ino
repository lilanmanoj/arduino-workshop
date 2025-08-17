#include<Arduino.h>

/** Constants **/
const unsigned int DATA_PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const unsigned int LED_SSD_GND_PINS[2] = {14, 15};
const unsigned int LED_GND_INDEX = 0;
const unsigned int SSD_GND_INDEX = 1;
const unsigned int PROG_DELAY = 5;
const unsigned int SWITCHING_PINS[4] = {16, 17, 18, 19};
const unsigned int COUNTER_CYCLES = 5;

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
unsigned int count = 0;
unsigned int cycles = 0;

void setup() {
    for (int x = 0; x < sizeof(DATA_PINS)/sizeof(DATA_PINS[0]); x++) {
        pinMode(DATA_PINS[x], OUTPUT);
    }

    for (int x = 0; x < sizeof(SWITCHING_PINS)/sizeof(SWITCHING_PINS[0]); x++) {
        pinMode(SWITCHING_PINS[x], OUTPUT);
    }

    for (int x = 0; x < sizeof(LED_SSD_GND_PINS)/sizeof(LED_SSD_GND_PINS[0]); x++) {
        pinMode(LED_SSD_GND_PINS[x], OUTPUT);
    }
}

void loop() {
    displayNumber(count);

    if (cycles == COUNTER_CYCLES) {
        count++;
        cycles = 0;
    } else {
        cycles++;
    }

    if (count == 10000) {
        count = 0;
    }

    delay(PROG_DELAY);
}

void displayNumber(unsigned int number) {
    unsigned int digits[4];

    digits[0] = number%10;
    digits[1] = (number/10)%10;
    digits[2] = (number/100)%10;
    digits[3] = (number/1000);

    for (int n = 0; n < 4; n++) {
        SSDSelect(n);
        SSDWrite(digits[n]);
        delay(5);
    }
}

void clearData() {
    for (int x = 0; x < sizeof(DATA_PINS)/sizeof(DATA_PINS[0]) ; x++) {
        digitalWrite(DATA_PINS[x], LOW);
    }
}

void clearSelection() {
    for (int x = 0; x < sizeof(SWITCHING_PINS)/sizeof(SWITCHING_PINS[0]) ; x++) {
        digitalWrite(SWITCHING_PINS[x], LOW);
    }
}

void SSDSelect(unsigned int idx) {
    clearSelection();
    digitalWrite(SWITCHING_PINS[idx], HIGH);
}

void SSDWrite(unsigned int digit) {
    clearData();
    digitalWrite(LED_SSD_GND_PINS[LED_GND_INDEX], HIGH);
    digitalWrite(LED_SSD_GND_PINS[SSD_GND_INDEX], LOW);

    unsigned int value = DIGIT_MAP[digit];

    for (int x = 0; x < 8; x++) {
        unsigned int mask = 1<<x;
        unsigned int check = value & mask;

        if (check == mask) {
            digitalWrite(DATA_PINS[x], HIGH);
        }
    }
}
