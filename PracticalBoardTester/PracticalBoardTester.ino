#include<Arduino.h>

const unsigned int MAX_CYCLE_COUNT = 1000;
const unsigned int DATA_PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const unsigned int SWITCHING_PINS[4] = {10, 11, 12, 13};
const unsigned int LED_SSD_PINS[2] = {18, 19};
const unsigned int LED_GND_INDEX = 0;
const unsigned int SSD_GND_INDEX = 1;
const unsigned int PROGRAM_DELAY = 10;
const unsigned int LED_CYCLES_MULTIPLIER = 10;
unsigned int global_cycle_count = 0;
unsigned int led_cycle_count = 0;
bool led_is_counting_up = true;
unsigned int led_current_index = 1;

void litLed(unsigned int idx);

void setup() {
    for (int x = 0; x < sizeof(DATA_PINS)/sizeof(DATA_PINS[0]) ; x++) {
        pinMode(x, OUTPUT);
    }

    for (int x = 0; x < sizeof(SWITCHING_PINS)/sizeof(DATA_PINS[0]) ; x++) {
        pinMode(x, OUTPUT);
    }

    for (int x = 0; x < sizeof(LED_SSD_PINS)/sizeof(DATA_PINS[0]) ; x++) {
        pinMode(x, OUTPUT);
    }
}

void loop() {
    global_cycle_count++;

    if (global_cycle_count%LED_CYCLES_MULTIPLIER == 0) {
        if (led_is_counting_up) {
            led_current_index = led_cycle_count + 1;
            led_is_counting_up = (led_cycle_count >= 7) ? false : true;
        } else {
            led_current_index = 8 - led_cycle_count;
            led_is_counting_up = (led_cycle_count >= 7) ? true : false;
        }

        led_cycle_count = (led_cycle_count < 7) ? led_cycle_count + 1 : 0;
    }
    
    litLed(led_current_index);

    global_cycle_count = (global_cycle_count == MAX_CYCLE_COUNT) ? 0 : global_cycle_count;
    
    delay(PROGRAM_DELAY);
}

void litLed(unsigned int idx) {
    digitalWrite(LED_SSD_PINS[LED_GND_INDEX], LOW);
    digitalWrite(LED_SSD_PINS[SSD_GND_INDEX], HIGH);
    digitalWrite(DATA_PINS[idx], HIGH);
}
