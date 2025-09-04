/*
* This requires the LiquidCrystal_I2C library.
* Install it using Arduino IDE Library Manager.
* Or from ardiuino-cli using:
* > arduino-cli lib install "LiquidCrystal_I2C"
*/
#include<Arduino.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String message = "Hello World";

void setup() {
    lcd.init();
    lcd.backlight();
    lcd.print(message);
}

void loop() {
}
