#include "Player.h"

Player player1("Player 1", 2, 5);
Player player2("Player 2", 3, 6);

void handlePlayer1Press() { player1.press(); }
void handlePlayer2Press() { player2.press(); }

void setup() {
  Serial.begin(9600);
  player1.init();
  player2.init();

  attachInterrupt(digitalPinToInterrupt(2), handlePlayer1Press, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), handlePlayer2Press, FALLING);

  Serial.println("Game starts now!");
}

void loop() {
  // Nothing needed here, everything handled in ISRs
}
