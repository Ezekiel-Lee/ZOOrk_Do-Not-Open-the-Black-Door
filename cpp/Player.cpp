//
// Created by Richard Skarbez on 5/7/23.
// Modified for Cthulhu Mythos theme.
//

#include "../header/Player.h"
#include <iostream>
#include <algorithm>

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

int Player::getSanity() const {
    return sanity;
}

void Player::drainSanity(int amount) {
    sanity = std::max(0, sanity - amount);
}

void Player::restoreSanity(int amount) {
    sanity = std::min(100, sanity + amount);
}

bool Player::isInsane() const {
    return sanity <= 0;
}

void Player::resetSanity() {
    sanity = 100;
}

void Player::clearInventory() {
    inventory.clear();
}
