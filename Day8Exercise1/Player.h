#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>

class Player {
  public:
    Player(const char* name, uint8_t buttonPin, uint8_t ledPin);

    void init();
    void press();
    void win();
    void block();

    bool isBlocked() const;
    bool hasAlreadyWon() const;

    static void registerPlayer(Player* p);
    static void blockOthers(Player* winner);

  private:
    const char* name;
    uint8_t buttonPin;
    uint8_t ledPin;
    bool blocked;
    bool hasWon;
    unsigned long lastPressTime;

    static Player* players[4];  // up to 2 players
    static uint8_t playerCount;
};

#endif
