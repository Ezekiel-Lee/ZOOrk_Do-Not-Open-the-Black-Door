//
// Door.cpp — Part 2 extension
//

#include "../header/Door.h"
#include <iostream>

Door::Door(const std::string &name, const std::string &description,
           Room* from, Room* to,
           const std::string &requiredItemName,
           const std::string &lockedMessage)
    : Passage(name, description, from, to),
      requiredItem(requiredItemName),
      lockedMsg(lockedMessage)
{}

void Door::enter() {
    Player* player = Player::instance();

    if (locked && !player->hasItem(requiredItem)) {
        std::cout << lockedMsg << "\n";
        // Stay in current room — do not move player
        player->setCurrentRoom(fromRoom);
    } else {
        locked = false;
        std::cout << "The door creaks open as you step through...\n";
        player->setCurrentRoom(toRoom);
        toRoom->enter();
    }
}

bool Door::isLocked() const {
    return locked;
}

void Door::unlock() {
    locked = false;
}
