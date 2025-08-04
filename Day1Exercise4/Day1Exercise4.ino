#include <Arduino.h>

const int LED_PIN = 5;
const int TIME_UNIT = 150;

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    dot(3); // S
    char_separator(); // Space between characters
    dash(3); // O
    char_separator(); // Space between characters
    dot(3); // S
    word_separator(); // Space between word
}

void dot(int num) {
    for (int i = 0; i < num; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(TIME_UNIT); // Dot duration
        digitalWrite(LED_PIN, LOW);
        delay(TIME_UNIT); // Space after dot
    }
}

void dash(int num) {
    for (int i = 0; i < num; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(TIME_UNIT * 3); // Dot duration
        digitalWrite(LED_PIN, LOW);
        delay(TIME_UNIT); // Space after dash
    }
}

void char_separator() {
    digitalWrite(LED_PIN, LOW);
    delay(TIME_UNIT * 2); // Space between characters
}

void word_separator() {
    digitalWrite(LED_PIN, LOW);
    delay(TIME_UNIT * 6); // Space between words
}
