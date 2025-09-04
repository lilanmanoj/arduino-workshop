/*
* This requires the LiquidCrystal_I2C library.
* Install it using Arduino IDE Library Manager.
* Or from ardiuino-cli using:
* > arduino-cli lib install "LiquidCrystal_I2C"
*/
#include<Arduino.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String scrollingText = "This is scrolling text demo!";

void setup() {
    lcd.init();
    // Uncomment below to turn on the blacklight
    // lcd.backlight();
}

void loop() {
    lcd.setCursor(0,0);
    lcd.scrollDisplayLeft();
    lcd.print(scrollingText);
    lcd.blink();

    delay(200);
}
