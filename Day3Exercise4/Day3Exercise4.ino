#include<Arduino.h>

/** Constants **/
const unsigned int DATA_PINS[8] = {15, 14, 7, 6, 5, 4, 3, 2};
const unsigned int DEBOUNCE_RELEASE_DELAY = 50;
const unsigned int LED_GND_PIN = 12;
const unsigned int PROG_DELAY = 100;
const unsigned int SW_PIN = 11;

/** Variables **/
unsigned char count = 0;
bool is_counting_up = true;

void setup() {
    for (int x = 0; x < sizeof(DATA_PINS)/sizeof(DATA_PINS[0]); x++) {
        pinMode(DATA_PINS[x], OUTPUT);
    }

    pinMode(SW_PIN, INPUT_PULLUP);
    pinMode(LED_GND_PIN, OUTPUT);
    digitalWrite(LED_GND_PIN, LOW);
}

void loop() {
    displayValue(count);

    if (digitalRead(SW_PIN) == LOW) {
        is_counting_up = !is_counting_up;
        
        while(digitalRead(SW_PIN) == LOW) {
            delay(DEBOUNCE_RELEASE_DELAY);
        }
    }

    if (is_counting_up && count == 256) {
        is_counting_up = false;
    } else if (!is_counting_up && count == 0) {
        is_counting_up = true;
    }

    count = (is_counting_up) ? count + 1 : count - 1;

    delay(PROG_DELAY);
}

void displayValue(unsigned int num) {
    for (int x = 0; x < sizeof(DATA_PINS)/sizeof(DATA_PINS[0]); x++) {
        digitalWrite(DATA_PINS[x], num & (1<<x));
    }
}
