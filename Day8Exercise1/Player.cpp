#include "Player.h"

Player* Player::players[4];
uint8_t Player::playerCount = 0;

Player::Player(const char* n, uint8_t btn, uint8_t led)
  : name(n), buttonPin(btn), ledPin(led), blocked(false), hasWon(false), lastPressTime(0) 
{
  // Auto-register player at creation
  if (playerCount < 4) {
    players[playerCount++] = this;
  }
}

void Player::init() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void Player::press() {
  if (blocked || hasWon) return;

  unsigned long now = millis();
  if (now - lastPressTime < 50) return; // debounce
  lastPressTime = now;

  win();
}

void Player::win() {
  hasWon = true;
  digitalWrite(ledPin, HIGH);
  Serial.print(name);
  Serial.println(" wins!");

  blockOthers(this);
}

void Player::block() {
  blocked = true;
}

bool Player::isBlocked() const { return blocked; }
bool Player::hasAlreadyWon() const { return hasWon; }

void Player::registerPlayer(Player* p) {
  if (playerCount < 4) {
    players[playerCount++] = p;
  }
}

void Player::blockOthers(Player* winner) {
  for (uint8_t i = 0; i < playerCount; i++) {
    if (players[i] != winner) {
      players[i]->block();
    }
  }
}
