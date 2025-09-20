#include<Arduino.h>

const uint8_t SSD_GND = 12;
const uint8_t SSD_SEGMENTS[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const uint8_t SSD_DIGITS[4] = {16, 17, 18, 19};
const uint8_t SSD_ENCODE[10] = {
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

const unsigned int FIXED_RESISTANCE = 1000;
const uint8_t APIN = 14;
int adc_val = 0;
float voltage = 0;
float resistance = 0;
char serial_in = NULL;
bool start_ssd = false;

void setup() {
    Serial.begin(9600);
    pinMode(APIN, INPUT);
    pinMode(SSD_GND, OUTPUT);
    digitalWrite(SSD_GND, LOW);

    uint8_t i = 0;

    for (i = 0; i < sizeof(SSD_SEGMENTS)/sizeof(SSD_SEGMENTS[0]); i++) {
        pinMode(SSD_SEGMENTS[i], OUTPUT);
    }

    for (i = 0; i < sizeof(SSD_DIGITS)/sizeof(SSD_DIGITS[0]); i++) {
        pinMode(SSD_DIGITS[i], OUTPUT);
    }
}

void loop() {
    adc_val = analogRead(APIN);
    voltage = adc_val * (5.0/1023);
    resistance = voltage * FIXED_RESISTANCE / (5.0 - voltage);

    if (Serial.available() > 0) {
        serial_in = Serial.read();
    }

    if (serial_in == 'b') {
        start_ssd = true;
    } else if (serial_in == 'd') {
        start_ssd = false;
    }

    if (start_ssd) {
        displayOnSSD((int)ceil(resistance));
    }
}

void displayOnSSD(int n) {
    uint8_t ones = n % 10;
    uint8_t tens = (n % 100) / 10;
    uint8_t hundreds = (n % 1000) / 100;
    uint8_t thousands = n / 1000;

    uint8_t digits[4] = {ones, tens, hundreds, thousands};

    for (uint8_t i = 0; i < sizeof(SSD_DIGITS)/sizeof(SSD_DIGITS[0]); i++) {
        writeToSSD(SSD_DIGITS[i], digits[i]);
        delay(2);
        digitalWrite(SSD_DIGITS[i], LOW);
    }
}

void writeToSSD(uint8_t ssd_pin, uint8_t digit) {
    digitalWrite(ssd_pin, HIGH);

    for (uint8_t i = 0; i < sizeof(SSD_SEGMENTS)/sizeof(SSD_SEGMENTS[0]); i++) {
        digitalWrite(SSD_SEGMENTS[i], SSD_ENCODE[digit] & 1<<i);
    }
}
