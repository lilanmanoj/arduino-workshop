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
