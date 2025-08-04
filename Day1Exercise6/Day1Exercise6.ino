#include <Arduino.h>

void setup() {
    for (int i = 2; i <= 9; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
}

void loop() {
    

    for (int x = 7; x >= 0; x--) {
        int high_pin = x + 2;

        digitalWrite(high_pin, HIGH);

        for (int y = 2; y < 10; y++) {
            if (y != high_pin) {
                digitalWrite(y, LOW);
            }
        }

        delay(50);
    }
}

void pattern(bool UP = true) {
    if (UP) {
        for (int x = 0; x <= 7; x++) {
            int high_pin = x + 2;

            digitalWrite(high_pin, HIGH);

            for (int y = 2; y < 10; y++) {
                if (y != high_pin) {
                    digitalWrite(y, LOW);
                }
            }

            delay(50);
        }
    }
}
