#include<Arduino.h>

/* Constants */
const unsigned int MAX_CYCLE_COUNT = 1000;
const unsigned int DATA_PINS[8] = {2, 3, 4, 5, 6, 7, 14, 15};
const unsigned int SWITCHING_PINS[4] = {16, 17, 18, 19};
const unsigned int LED_SSD_PINS[2] = {12, 13};
const unsigned int LED_GND_INDEX = 0;
const unsigned int SSD_GND_INDEX = 1;
const unsigned int PROGRAM_DELAY = 5;
const unsigned int LED_CYCLES_MULTIPLIER = 10;
unsigned int global_cycle_count = 0;
unsigned int led_cycle_count = 0;
bool led_is_counting_up = true;
unsigned int led_current_index = 0;

/* SSD */
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

/* Functions */
void clearData(void);
void clearSelection(void);
void LEDWrite(unsigned int idx);
void SSDSelect(unsigned int idx);
void SSDWrite(unsigned int digit);

void setup() {
    for (int x = 0; x < sizeof(DATA_PINS)/sizeof(DATA_PINS[0]); x++) {
        pinMode(DATA_PINS[x], OUTPUT);
    }

    for (int x = 0; x < sizeof(SWITCHING_PINS)/sizeof(SWITCHING_PINS[0]); x++) {
        pinMode(SWITCHING_PINS[x], OUTPUT);
    }

    for (int x = 0; x < sizeof(LED_SSD_PINS)/sizeof(LED_SSD_PINS[0]); x++) {
        pinMode(LED_SSD_PINS[x], OUTPUT);
    }
}

void loop() {
    global_cycle_count++;

    if (global_cycle_count%LED_CYCLES_MULTIPLIER == 0) {
        led_cycle_count = (led_cycle_count < 7) ? led_cycle_count + 1 : 0;

        if (led_is_counting_up) {
            led_current_index = led_cycle_count;
            led_is_counting_up = (led_cycle_count >= 7) ? false : true;
        } else {
            led_current_index = 7 - led_cycle_count;
            led_is_counting_up = (led_cycle_count >= 7) ? true : false;
        }        
    } 
    
    LEDWrite(led_current_index);

    delay(PROGRAM_DELAY);

    SSDSelect(0);
    SSDWrite(9);

    global_cycle_count = (global_cycle_count == MAX_CYCLE_COUNT) ? 0 : global_cycle_count;

    delay(PROGRAM_DELAY);
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

void LEDWrite(unsigned int idx) {
    clearData();
    digitalWrite(LED_SSD_PINS[LED_GND_INDEX], LOW);
    digitalWrite(LED_SSD_PINS[SSD_GND_INDEX], HIGH);
    digitalWrite(DATA_PINS[idx], HIGH);
}

void SSDSelect(unsigned int idx) {
    clearSelection();
    digitalWrite(SWITCHING_PINS[idx], HIGH);
}

void SSDWrite(unsigned int digit) {
    clearData();
    digitalWrite(LED_SSD_PINS[LED_GND_INDEX], HIGH);
    digitalWrite(LED_SSD_PINS[SSD_GND_INDEX], LOW);

    unsigned int value = DIGIT_MAP[digit];

    for (int x = 0; x < 8; x++) {
        unsigned int mask = 1<<x;
        unsigned int check = value & mask;

        if (check == mask) {
            digitalWrite(DATA_PINS[x], HIGH);
        }
    }
}
