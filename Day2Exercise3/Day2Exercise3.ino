#include<Arduino.h>

bool count_down = false;
int count = 0;

void led_out(int c);

void setup() {
    for (int i = 2; i < 10; i++) {
        pinMode(i, OUTPUT);
    }
}

void loop() {
    led_out(count);

    if (!count_down) {
        if (count < 255) {
            count++;
        } else {
            count_down = true;
        }
    } else {
        if (count > 0) {
            count--;
        } else if (count == 0) {
            count_down = false;
        }
    }

    delay(100);
}

void led_out(int c) {
    for (int i = 2; i < 10; i++) {
        digitalWrite(i, LOW);
    }

    if (count > 0) {
        for (int i = 0; i < 8; i++) {
            int masked = c & (1 << i);

            if (masked == (1 << i)) {
                digitalWrite(i, HIGH);
            }
        }
    }
}
