#include <memory>
//
// Created by Richard Skarbez on 5/7/23.
//

#include "../header/RoomDefaultEnterCommand.h"

void RoomDefaultEnterCommand::execute() {
    std::cout << gameObject->getDescription() << "\n";
}