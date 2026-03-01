// Potentiometer is connected to GPIO 1 (Analog ADC1_CH1)
#define POT_PIN 1

// variable for storing the potentiometer value
int potValue = 0;
float voltage = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // Reading potentiometer value
  potValue = analogRead(POT_PIN);
  voltage = (potValue * 3.3) / 4095.0;

  Serial.printf("%d\t%f\n", potValue, voltage);
}