#include<Arduino.h>
#include<LiquidCrystal_I2C.h>

const uint8_t ADC_PIN = 14;
const uint8_t SW_PIN = 15;
const uint8_t PROG_DELAY = 150;
const uint8_t DEBOUNCE_DELAY = 50;

LiquidCrystal_I2C lcd(0x27, 16, 2);

uint16_t adc_val = 0;
float current_voltage = 0;
float threshold_voltage = 0;
String str_second_line = "";

void setup() {
    lcd.init();
    lcd.backlight();

    pinMode(ADC_PIN, INPUT);
    pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {
    adc_val = analogRead(ADC_PIN);
    current_voltage = adc_val * (5/1023.0);

    if (digitalRead(SW_PIN) == LOW) {
        while (digitalRead(SW_PIN) == LOW) {
            delay(DEBOUNCE_DELAY);
        }

        threshold_voltage = current_voltage;
    }

    if (current_voltage > threshold_voltage) {
        str_second_line = "ALERT:Over Voltage";
    } else {
        str_second_line = "Threshold: ";
        str_second_line.concat(threshold_voltage);
        str_second_line.concat("V");
    }

    lcd.setCursor(0,0);
    lcd.print("Voltage: ");
    lcd.print(current_voltage);
    lcd.print("V");

    lcd.setCursor(0,1);
    lcd.print(str_second_line);

    delay(PROG_DELAY);
}
