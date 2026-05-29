//
// PhraseDoor.cpp
//
#include "../header/PhraseDoor.h"
#include "../header/Player.h"
#include <iostream>

PhraseDoor::PhraseDoor(const std::string &name, const std::string &description,
                       Room* from, Room* to,
                       const std::string &requiredPhrase,
                       const std::string &lockedMessage,
                       const std::set<std::string> &knownPhrases)
    : Passage(name, description, from, to),
      requiredPhrase(requiredPhrase),
      lockedMsg(lockedMessage),
      knownPhrases(knownPhrases)
{}

void PhraseDoor::enter() {
    Player* player = Player::instance();

    if (knownPhrases.find(requiredPhrase) == knownPhrases.end()) {
        std::cout << lockedMsg << "\n";
        player->setCurrentRoom(fromRoom);
    } else {
        std::cout << "The gate shudders. Ancient stone grinds against stone.\n";
        std::cout << "The phrase echoes back at you from every surface, growing\n";
        std::cout << "louder and louder until silence swallows it whole.\n";
        std::cout << "The way is open.\n";
        player->setCurrentRoom(toRoom);
        toRoom->enter();
    }
}
