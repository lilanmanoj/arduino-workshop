/*
* This print scrollable text and non scrollable count on 16x2 LCD.
* Simultaneously, to scroll and to increment the count, in diffferent time intervals for each.
*
* Note:
* This requires the LiquidCrystal_I2C library.
* Install it using Arduino IDE Library Manager.
* Or from ardiuino-cli using:
* > arduino-cli lib install "LiquidCrystal_I2C"
*/
#include<Arduino.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const unsigned char PROG_DELAY = 50; // milliseconds
unsigned int count = 0;
String scrollingText = "  ** This is scrolling text demo! **  ";
unsigned long previousMillis_counter = 0;
unsigned long previousMillis_scroll = 0;

void setup() {
    lcd.init();
    lcd.noBlink();
    lcd.backlight();
}

void loop() {
    if (millis() - previousMillis_scroll >= 150) {
        previousMillis_scroll = millis();
        
        // Simulating the scrolling text
        scrollingText = scrollingText.substring(1) + scrollingText.charAt(0);
    }
    
    if (millis() - previousMillis_counter >= 1000) {
        previousMillis_counter = millis();

        lcd.clear();

        // Incrementing the count variable or resetting
        count = (count < 10) ? count + 1 : 0;
    }

    // After 10 seconds, turn off the backlight
    if (millis() >= 10000) {
        lcd.noBacklight();
    }

    // Printing on LCD
    lcd.setCursor(0,0);
    lcd.print(scrollingText);

    lcd.setCursor(0,1);
    lcd.print("Count: ");
    lcd.print(count);

    delay(PROG_DELAY);
}
