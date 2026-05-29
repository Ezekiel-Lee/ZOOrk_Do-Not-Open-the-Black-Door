//
// PhraseDoor.h — A door that requires the player to know a specific phrase.
// The player must type: say <phrase> while standing before the door's room,
// which unlocks it; then "go down" passes through normally.
// Alternatively, the engine checks knownPhrases on enter().
//
#ifndef ZOORK_PHRASEDOOR_H
#define ZOORK_PHRASEDOOR_H

#include "Passage.h"
#include <set>
#include <string>

class PhraseDoor : public Passage {
public:
    PhraseDoor(const std::string &name, const std::string &description,
               Room* from, Room* to,
               const std::string &requiredPhrase,
               const std::string &lockedMessage,
               const std::set<std::string> &knownPhrases);

    void enter() override;

private:
    std::string requiredPhrase;
    std::string lockedMsg;
    const std::set<std::string> &knownPhrases;  // reference to engine's set
};

#endif //ZOORK_PHRASEDOOR_H
