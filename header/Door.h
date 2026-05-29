//
// Door.h — Part 2 extension: Door deriving from Passage.
// Requires the player to possess a specific Item to pass through.
//

#ifndef ZOORK_DOOR_H
#define ZOORK_DOOR_H

#include "Passage.h"
#include "Player.h"
#include <string>

class Door : public Passage {
public:
    Door(const std::string &name, const std::string &description,
         Room* from, Room* to,
         const std::string &requiredItemName,
         const std::string &lockedMessage);

    // Override enter: check if player has the key item
    void enter() override;

    bool isLocked() const;
    void unlock();

private:
    std::string requiredItem;
    std::string lockedMsg;
    bool locked = true;
};

#endif //ZOORK_DOOR_H
