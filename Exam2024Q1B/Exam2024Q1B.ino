#include<Arduino.h>

const uint8_t LEDS[4] = {3,5,6,9};
const uint8_t SW[2] = {14,15};
const uint8_t LED_GND = 11;
const uint8_t DEBOUNCE_DELAY = 50;

uint8_t led_index = 0;
uint8_t brightness = 100;
uint8_t pwm_val = 255;

void setup() {
    uint8_t i = 0;

    for (i = 0; i < sizeof(LEDS)/sizeof(LEDS[0]); i++) {
        pinMode(LEDS[i], OUTPUT);
    }

    for (i = 0; i < sizeof(SW)/sizeof(SW[0]); i++) {
        pinMode(SW[i], INPUT_PULLUP);
    }

    pinMode(LED_GND, OUTPUT);
    digitalWrite(LED_GND, LOW);
}

void loop() {
    if (digitalRead(SW[0]) == LOW) {
        while (digitalRead(SW[0]) == LOW) {
            delay(DEBOUNCE_DELAY);
        }

        digitalWrite(LEDS[led_index], LOW);
        led_index = (led_index < 3) ? led_index + 1 : 0;
    }

    if (digitalRead(SW[1]) == LOW) {
        while (digitalRead(SW[1]) == LOW) {
            delay(DEBOUNCE_DELAY);
        }

        brightness = (brightness < 100) ? brightness + 25 : 0;
    }

    pwm_val = map(brightness, 0, 100, 0, 255);

    analogWrite(LEDS[led_index], pwm_val);
}
