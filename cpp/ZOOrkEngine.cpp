//
// Created by Richard Skarbez on 5/7/23.
// Modified for Cthulhu Mythos theme — multi-ending system.
//

#include "../header/ZOOrkEngine.h"

#include <utility>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start, std::shared_ptr<Room> chamber) {
    player = Player::instance();
    startRoom   = start.get();
    chamberRoom = chamber.get();
    player->setCurrentRoom(startRoom);
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    std::cout << "\n=== Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn ===\n";
    std::cout << "(Commands: go <dir>, look [item], take <item>, drop <item>,\n";
    std::cout << "           use <item>, inventory, sanity, read <item>, quit)\n\n";

    while (!gameOver) {
        checkSanity();
        if (gameOver) break;

        std::cout << "\n> ";

        std::string input;
        std::getline(std::cin, input);
        if (input.empty()) continue;

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if (command == "look" || command == "inspect" || command == "examine") {
            handleLookCommand(arguments);
        } else if (command == "take" || command == "get") {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "inventory" || command == "inv" || command == "i") {
            handleInventoryCommand(arguments);
        } else if (command == "sanity" || command == "status") {
            handleSanityCommand(arguments);
        } else if (command == "read") {
            handleReadCommand(arguments);
        } else if (command == "use") {
            handleUseCommand(arguments);
        } else if (command == "quit" || command == "exit") {
            handleQuitCommand(arguments);
        } else {
            std::cout << "The eldritch void offers no response to \"" << command << "\".\n";
        }
    }
}

// ─── go ──────────────────────────────────────────────────────────────────────
void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Go where? (north, south, east, west, up, down)\n";
        return;
    }

    std::string direction;
    const std::string &arg = arguments[0];
    if      (arg == "n" || arg == "north") direction = "north";
    else if (arg == "s" || arg == "south") direction = "south";
    else if (arg == "e" || arg == "east")  direction = "east";
    else if (arg == "w" || arg == "west")  direction = "west";
    else if (arg == "u" || arg == "up")    direction = "up";
    else if (arg == "d" || arg == "down")  direction = "down";
    else direction = arg;

    Room* previousRoom = player->getCurrentRoom();
    auto passage = previousRoom->getPassage(direction);
    passage->enter();

    Room* newRoom = player->getCurrentRoom();
    if (newRoom != previousRoom) {
        int drain = newRoom->getSanityDrain();
        if (drain > 0) {
            player->drainSanity(drain);
            std::cout << "[The horrors here erode your mind. Sanity -" << drain
                      << " | Now: " << player->getSanity() << "/100]\n";
        }
        checkEnding();
    }
}

// ─── look ────────────────────────────────────────────────────────────────────
void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        Room* room = player->getCurrentRoom();
        std::cout << "\n[ " << room->getName() << " ]\n";
        std::cout << room->getDescription() << "\n";

        auto roomItems = room->getItems();
        if (!roomItems.empty()) {
            std::cout << "You see here:\n";
            for (const auto &item : roomItems)
                std::cout << "  - " << item->getName() << "\n";
        } else {
            std::cout << "There is nothing of obvious interest here.\n";
        }
    } else {
        std::string target = arguments[0];
        Room* room = player->getCurrentRoom();

        auto roomItem = room->getItem(target);
        if (roomItem) { std::cout << roomItem->getDescription() << "\n"; return; }

        auto invItem = player->getItem(target);
        if (invItem) { std::cout << invItem->getDescription() << "\n"; return; }

        std::cout << "You see no \"" << target << "\" here.\n";
    }
}

// ─── take ────────────────────────────────────────────────────────────────────
void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) { std::cout << "Take what?\n"; return; }
    std::string target = arguments[0];
    Room* room = player->getCurrentRoom();

    auto item = room->getItem(target);
    if (!item) { std::cout << "There is no \"" << target << "\" here to take.\n"; return; }

    room->removeItem(target);
    player->addItem(item);
    std::cout << "You take the " << item->getName() << ".\n";

    if (item->getName() == "necronomicon" || item->getName() == "cultist-robe") {
        std::cout << "As your fingers close around it, your mind recoils...\n";
        player->drainSanity(10);
        std::cout << "  [Sanity -10 | Now: " << player->getSanity() << "/100]\n";
    }
}

// ─── drop ────────────────────────────────────────────────────────────────────
void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) { std::cout << "Drop what?\n"; return; }
    std::string target = arguments[0];

    auto item = player->getItem(target);
    if (!item) { std::cout << "You are not carrying a \"" << target << "\".\n"; return; }

    player->removeItem(target);
    player->getCurrentRoom()->addItem(item);
    std::cout << "You drop the " << item->getName() << ".\n";
}

// ─── inventory ───────────────────────────────────────────────────────────────
void ZOOrkEngine::handleInventoryCommand(std::vector<std::string> arguments) {
    auto inv = player->getInventory();
    if (inv.empty()) {
        std::cout << "You carry nothing but the weight of forbidden knowledge.\n";
    } else {
        std::cout << "You are carrying:\n";
        for (const auto &item : inv)
            std::cout << "  - " << item->getName() << "\n";
    }
}

// ─── sanity ──────────────────────────────────────────────────────────────────
void ZOOrkEngine::handleSanityCommand(std::vector<std::string> arguments) {
    int s = player->getSanity();
    std::cout << "Sanity: " << s << "/100  ";
    if      (s >= 80) std::cout << "[Stable]\n";
    else if (s >= 60) std::cout << "[Unsettled — strange thoughts intrude]\n";
    else if (s >= 40) std::cout << "[Disturbed — reality feels thin]\n";
    else if (s >= 20) std::cout << "[Unravelling — the void whispers your name]\n";
    else              std::cout << "[Critical — Cthulhu's gaze is upon you]\n";
}

// ─── read ────────────────────────────────────────────────────────────────────
void ZOOrkEngine::handleReadCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) { std::cout << "Read what?\n"; return; }
    std::string target = arguments[0];

    auto item = player->getItem(target);
    if (!item) item = player->getCurrentRoom()->getItem(target);
    if (!item) { std::cout << "You see no \"" << target << "\" to read.\n"; return; }

    if (target == "journal") {
        std::cout << "The journal reads:\n";
        std::cout << "  'Do not go to the docks after dark. Do not look at the water.\n";
        std::cout << "   Do not listen to the chanting. Above all — do not open the\n";
        std::cout << "   black door beneath the church. God help us all.'\n";
    } else if (target == "necronomicon") {
        std::cout << "The pages writhe with symbols that should not exist.\n";
        std::cout << "You understand fragments — terrible, universe-shattering fragments.\n";
        player->drainSanity(20);
        std::cout << "  [Sanity -20 | Now: " << player->getSanity() << "/100]\n";
        std::cout << "Among the madness, one phrase burns into your mind: \"ia-fhtagn\"\n";
        std::cout << "  [You have learned the phrase: ia-fhtagn]\n";
        knownPhrases.insert("ia-fhtagn");
    } else {
        std::cout << "You examine the " << item->getName() << " but find nothing readable.\n";
    }
}

// ─── use ─────────────────────────────────────────────────────────────────────
void ZOOrkEngine::handleUseCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) { std::cout << "Use what?\n"; return; }
    std::string target = arguments[0];

    auto item = player->getItem(target);
    if (!item) { std::cout << "You are not carrying a \"" << target << "\".\n"; return; }

    if (target == "deep-one-idol") {
        if (player->getCurrentRoom() == chamberRoom) {
            showTrueEnding();
            return;
        } else {
            std::cout << "You hold up the idol. It hums faintly, as if yearning\n";
            std::cout << "for somewhere deeper. This is not the right place.\n";
            return;
        }
    }

    if (target == "laudanum") {
        std::cout << "An unknown force seeps into you.\n";
        std::cout << "A piece of your mind fades away.\n";
        player->restoreSanity(25);
        std::cout << "  [Sanity +25 | Now: " << player->getSanity() << "/100]\n";
        player->removeItem("laudanum");
    } else if (target == "prayer-book") {
        if (prayerBookUses <= 0) {
            std::cout << "You open the prayer book, but the words blur and offer no comfort.\n";
            std::cout << "Its power is spent.\n";
            return;
        }
        std::cout << "You pray to the Father in Heaven.\n";
        std::cout << "A calm settles over your mind.\n";
        player->restoreSanity(15);
        prayerBookUses--;
        std::cout << "  [Sanity +15 | Now: " << player->getSanity() << "/100]";
        std::cout << "  [Prayer book: " << prayerBookUses << " use(s) remaining]\n";
    } else if (target == "flare") {
        std::cout << "It was a brief but intense light.\n";
        std::cout << "A calm settles over your mind.\n";
        player->restoreSanity(5);
        std::cout << "  [Sanity +5 | Now: " << player->getSanity() << "/100]\n";
        player->removeItem("flare");
    } else {
        std::cout << "You turn the " << item->getName() << " over in your hands, but aren't sure how to use it.\n";
    }
}

// ─── quit ────────────────────────────────────────────────────────────────────
void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::getline(std::cin, input);
    if (makeLowercase(input) == "y" || makeLowercase(input) == "yes")
        gameOver = true;
}

// ─── ending checks ───────────────────────────────────────────────────────────
void ZOOrkEngine::checkEnding() {
    if (player->getCurrentRoom() == chamberRoom) {
        if (!player->hasItem("deep-one-idol")) {
            showNormalEnding();
        }
        // idol 소지 시: "use deep-one-idol" 커맨드를 기다림
    }
}

void ZOOrkEngine::checkSanity() {
    if (player->isInsane()) {
        showBadEnding();
        return;
    }
    printSanityWarning();
}

// ─── endings ─────────────────────────────────────────────────────────────────

// 공통 리셋 헬퍼
void ZOOrkEngine::resetGame() {
    player->resetSanity();
    player->clearInventory();
    knownPhrases.clear();
    prayerBookUses = 3;
    player->setCurrentRoom(startRoom);
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::showBadEnding() {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "  ║                  *** BAD ENDING ***                     ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║  The mortal who sought the truth of the world            ║\n";
    std::cout << "  ║  could not bear the weight of what lay beyond.           ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║  Before the truth was reached, the mind shattered —      ║\n";
    std::cout << "  ║  consumed by the void, lost to the endless dark.         ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║  Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn.    ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║                    GAME OVER                             ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║   [1] Try Again    [2] Quit                              ║\n";
    std::cout << "  ╚══════════════════════════════════════════════════════════╝\n";
    std::cout << "\n  Your choice: ";

    std::string input;
    std::getline(std::cin, input);

    if (input == "1") {
        std::cout << "\n  The nightmare releases you. You find yourself back at the station...\n\n";
        resetGame();
    } else {
        gameOver = true;
    }
}

void ZOOrkEngine::showNormalEnding() {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "  ║                 *** NORMAL ENDING ***                   ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║  The truth of the world lay just beyond your grasp.      ║\n";
    std::cout << "  ║  You stood at the threshold of eternity and turned away. ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║  You did not reach the final truth —                     ║\n";
    std::cout << "  ║  yet against all reason, you survived.                   ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║  Perhaps some truths are better left undiscovered.       ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║                  ~~~ YOU SURVIVED ~~~                    ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║   [1] Try Again    [2] Quit                              ║\n";
    std::cout << "  ╚══════════════════════════════════════════════════════════╝\n";
    std::cout << "\n  Your choice: ";

    std::string input;
    std::getline(std::cin, input);

    if (input == "1") {
        std::cout << "\n  The world resets. You find yourself back at the station...\n\n";
        resetGame();
    } else {
        gameOver = true;
    }
}

void ZOOrkEngine::showTrueEnding() {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "  ║                  *** TRUE ENDING ***                    ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║  You, a mortal, have reached the truth of the world.     ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║  You placed the idol upon the altar. The great eye       ║\n";
    std::cout << "  ║  of Cthulhu opened — and for one eternal moment,         ║\n";
    std::cout << "  ║  two minds touched across the gulf of aeons.             ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║  The universe is vast. Humanity is brief.                ║\n";
    std::cout << "  ║  And yet you stood here, unbroken, and looked upon it.   ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║  Your name shall be remembered for all eternity.         ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║              ~~~ THE TRUTH IS YOURS ~~~                  ║\n";
    std::cout << "  ║                                                          ║\n";
    std::cout << "  ║   [1] Play Again   [2] Quit                              ║\n";
    std::cout << "  ╚══════════════════════════════════════════════════════════╝\n";
    std::cout << "\n  Your choice: ";

    std::string input;
    std::getline(std::cin, input);

    if (input == "1") {
        std::cout << "\n  Time folds. The station awaits once more...\n\n";
        resetGame();
    } else {
        gameOver = true;
    }
}

void ZOOrkEngine::printSanityWarning() {
    int s = player->getSanity();
    if      (s <= 20 && s > 0) std::cout << "[WARNING: Your sanity is critically low! — " << s << "/100]\n";
    else if (s <= 40)          std::cout << "[The walls breathe. Something is watching you. — " << s << "/100]\n";
}

// ─── helpers ─────────────────────────────────────────────────────────────────
std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    while (std::getline(ss, token, ' ')) {
        if (!token.empty())
            tokens.push_back(makeLowercase(token));
    }
    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);
    return output;
}
