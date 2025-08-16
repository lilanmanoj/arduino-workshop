#include<Arduino.h>

const unsigned int DATA_PINS[8] = {15, 14, 7, 6, 5, 4, 3, 2};
const unsigned int LED_GND_PIN = 12;
const unsigned int SW_PIN = 11;
const int DEBOUNCE_RELEASE_DELAY = 50;
bool is_counting_up = true;
unsigned int count = 0;

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
        count = (is_counting_up) ? count + 1 : count - 1;
        
        while(digitalRead(SW_PIN) == LOW) {
            delay(DEBOUNCE_RELEASE_DELAY);
        }
    }

    if (is_counting_up && count == 256) {
        is_counting_up = false;
    } else if (!is_counting_up && count == 0) {
        is_counting_up = true;
    }
}

void displayValue(unsigned int num) {
    for (int x = 0; x < sizeof(DATA_PINS)/sizeof(DATA_PINS[0]); x++) {
        digitalWrite(DATA_PINS[x], num & (1<<x));
    }
}
