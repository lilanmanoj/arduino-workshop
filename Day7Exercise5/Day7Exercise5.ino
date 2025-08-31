#include<Arduino.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned int count = 0;

void setup() {
    lcd.init();
    lcd.backlight();
}

void loop() {
    lcd.clear();
    lcd.setCursor(0,0);

    lcd.print("Count: ");
    lcd.print(count);

    count = (count < 10) ? count + 1 : 0;

    delay(500);
}
