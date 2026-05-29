//
// Created by Richard Skarbez on 5/7/23.
// Modified for Cthulhu Mythos theme.
//

#ifndef ZOORK_ZOORKENGINE_H
#define ZOORK_ZOORKENGINE_H

#include "Player.h"
#include "Location.h"
#include "Passage.h"
#include <iostream>
#include <sstream>
#include <set>
#include <string>
#include <vector>

class ZOOrkEngine {
public:
    ZOOrkEngine(std::shared_ptr<Room> start, std::shared_ptr<Room> chamber);

    void run();

    // Exposed so PhraseDoor can hold a reference to it
    std::set<std::string> knownPhrases;

private:
    bool gameOver = false;
    Player *player;

    void handleGoCommand(std::vector<std::string>);
    void handleLookCommand(std::vector<std::string>);
    void handleTakeCommand(std::vector<std::string>);
    void handleDropCommand(std::vector<std::string>);
    void handleInventoryCommand(std::vector<std::string>);
    void handleSanityCommand(std::vector<std::string>);
    void handleReadCommand(std::vector<std::string>);
    void handleUseCommand(std::vector<std::string>);
    void handleQuitCommand(std::vector<std::string>);

    void checkSanity();
    void checkEnding();          // called on every room entry
    void showBadEnding();
    void showNormalEnding();
    void showTrueEnding();
    void printSanityWarning();

    Room* startRoom   = nullptr;
    Room* chamberRoom = nullptr;

    int prayerBookUses = 3;  // prayer-book can be used 3 times

    static std::vector<std::string> tokenizeString(const std::string&);
    static std::string makeLowercase(std::string);
};

#endif //ZOORK_ZOORKENGINE_H
