#include<Arduino.h>

const int SW = 11;
const int LED = 13;
const int DEBOUNCE_DELAY = 50;
const int DEBOUNCE_RELEASE_DELAY = 50;
bool toggle = false;

void setup() {
    pinMode(SW, INPUT);
    pinMode(LED, OUTPUT);
}

void loop() {
    if (digitalRead(SW) == HIGH) {
        delay(DEBOUNCE_DELAY);

        if (digitalRead(SW) == HIGH) {
            toggle = !toggle;

            // Wait for button release
            while (digitalRead(SW) == HIGH) {
                delay(DEBOUNCE_RELEASE_DELAY);
            }
        }
    }

    if (toggle) {
        digitalWrite(LED, HIGH);
    } else {
        digitalWrite(LED, LOW);
    }
}
