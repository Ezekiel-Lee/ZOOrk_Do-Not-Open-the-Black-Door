#include <memory>
//
// Created by Richard Skarbez on 5/7/23.
//

#include "../header/NullCommand.h"
#include "../header/NullRoom.h"

NullRoom::NullRoom() : Room("Nowhere", "This is a nonplace.", std::make_shared<NullCommand>()) {}