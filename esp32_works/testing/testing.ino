/**
 * Testing esp32 using built-in rgb led
 * 
 * Compiling note:
 * if the board fqbn is showing as esp32:esp32:esp32_family then instead of that
 * as an example use esp32:esp32:esp32s3 as the fqbn when compiling and uploading,
 * if the underlying chip is esp32s3.
 * otherwise use appropriate chip name replacing `esp32_family`
 */

void setup() {
    #ifdef RGB_BUILTIN
        pinMode(RGB_BUILTIN, OUTPUT);
    #endif
}

void loop() {
    #ifdef RGB_BUILTIN
        digitalWrite(RGB_BUILTIN, HIGH);  // Turn the RGB LED white
        delay(1000);
        digitalWrite(RGB_BUILTIN, LOW);  // Turn the RGB LED off
        delay(1000);

        rgbLedWrite(RGB_BUILTIN, RGB_BRIGHTNESS, 0, 0);  // Red
        delay(1000);
        rgbLedWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0);  // Green
        delay(1000);
        rgbLedWrite(RGB_BUILTIN, 0, 0, RGB_BRIGHTNESS);  // Blue
        delay(1000);
        rgbLedWrite(RGB_BUILTIN, 0, 0, 0);  // Off / black
        delay(1000);
    #endif
}
