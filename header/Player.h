//
// Created by Richard Skarbez on 5/7/23.
// Modified for Cthulhu Mythos theme — Sanity system added.
//

#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"

class Player : public Character {
public:
    static Player *instance() {
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room*);
    Room* getCurrentRoom() const;

    // Sanity system
    int getSanity() const;
    void drainSanity(int amount);
    void restoreSanity(int amount);
    bool isInsane() const;
    void resetSanity();
    void clearInventory();

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    Room* currentRoom;
    int sanity = 100;

    Player() : Character("You", "A lone investigator drawn to Innsmouth by rumours of gold."),
               currentRoom(new NullRoom()) {}
};

#endif //ZOORK_PLAYER_H
