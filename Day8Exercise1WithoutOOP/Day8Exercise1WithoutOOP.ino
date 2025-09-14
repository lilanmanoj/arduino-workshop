#include <Arduino.h>

const uint8_t PLAYER1_BUTTON_PIN = 2;
const uint8_t PLAYER1_LED_PIN    = 5;

const uint8_t PLAYER2_BUTTON_PIN = 3;
const uint8_t PLAYER2_LED_PIN    = 6;

volatile bool player1Won = false;
volatile bool player2Won = false;
volatile bool gameOver = false;

volatile unsigned long lastPressP1 = 0;
volatile unsigned long lastPressP2 = 0;
const unsigned long debounceDelay = 50;

// ISR
void handlePlayer1Press() {
  if (gameOver) return;  // ignore if someone already won

  unsigned long now = millis();
  if (now - lastPressP1 < debounceDelay) return;  // debounce
  lastPressP1 = now;

  player1Won = true;
  gameOver = true;
}

void handlePlayer2Press() {
  if (gameOver) return;  // ignore if someone already won

  unsigned long now = millis();
  if (now - lastPressP2 < debounceDelay) return;  // debounce
  lastPressP2 = now;

  player2Won = true;
  gameOver = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(PLAYER1_BUTTON_PIN, INPUT_PULLUP);
  pinMode(PLAYER1_LED_PIN, OUTPUT);
  digitalWrite(PLAYER1_LED_PIN, LOW);

  pinMode(PLAYER2_BUTTON_PIN, INPUT_PULLUP);
  pinMode(PLAYER2_LED_PIN, OUTPUT);
  digitalWrite(PLAYER2_LED_PIN, LOW);

  attachInterrupt(digitalPinToInterrupt(PLAYER1_BUTTON_PIN), handlePlayer1Press, FALLING);
  attachInterrupt(digitalPinToInterrupt(PLAYER2_BUTTON_PIN), handlePlayer2Press, FALLING);

  Serial.println("Game starts now!");
}

void loop() {
  if (gameOver) {
    if (player1Won) {
      digitalWrite(PLAYER1_LED_PIN, HIGH);
      Serial.println("Player 1 wins!");
    } else if (player2Won) {
      digitalWrite(PLAYER2_LED_PIN, HIGH);
      Serial.println("Player 2 wins!");
    }

    delay(2000); // wait 2 seconds before reset
    resetGame();
  }
}

void resetGame() {
  digitalWrite(PLAYER1_LED_PIN, LOW);
  digitalWrite(PLAYER2_LED_PIN, LOW);

  player1Won = false;
  player2Won = false;
  gameOver = false;

  Serial.println("New round!");
  Serial.println("Game starts now!");
}
