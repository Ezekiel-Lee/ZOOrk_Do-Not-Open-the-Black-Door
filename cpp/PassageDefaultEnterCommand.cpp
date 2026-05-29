#include <memory>
//
// Created by Richard Skarbez on 5/7/23.
// Modified: also moves the player to the destination room.
//

#include "../header/Passage.h"
#include "../header/PassageDefaultEnterCommand.h"
#include "../header/Player.h"

void PassageDefaultEnterCommand::execute() {
    Passage* passage = static_cast<Passage*>(gameObject);
    Room* dest = passage->getTo();
    Player::instance()->setCurrentRoom(dest);
    dest->enter();
}
