#include<Arduino.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

/** Const **/
const unsigned int BUZZER = 3;
const unsigned int PROG_DELAY = 5;
const float THRESHOLD = 3.5;

/** Vars **/
int ADCVal = 0;
float Varef = 5;

void setup() {
    lcd.init();
    lcd.backlight();

    pinMode(A0, INPUT);
    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);
}

void loop() {
    ADCVal = analogRead(A0);
    float sigVolt = (Varef/1024) * ADCVal;

    lcd.clear();
    lcd.setCursor(0,0);

    lcd.print("Voltage: ");
    lcd.print(sigVolt);
    lcd.print("V");

    lcd.setCursor(0,1);
    lcd.print("Threshold: ");
    lcd.print(THRESHOLD);
    lcd.print("V");

    if (sigVolt > THRESHOLD) {
        digitalWrite(BUZZER, HIGH);
    } else {
        digitalWrite(BUZZER, LOW);
    }

    delay(PROG_DELAY);
}
