//
// Created by Richard Skarbez on 5/7/23.
// Modified for Cthulhu Mythos theme.
//

#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "Character.h"
#include "RoomDefaultEnterCommand.h"
#include "Item.h"
#include "Location.h"
#include <map>
#include <vector>
#include <algorithm>

class Passage;

class Room : public Location {
public:
    Room(const std::string &, const std::string &);
    Room(const std::string &, const std::string &, std::shared_ptr<Command>);

    // Item management
    void addItem(std::shared_ptr<Item>);
    void removeItem(const std::string &);
    std::shared_ptr<Item> getItem(const std::string &);
    std::vector<std::shared_ptr<Item>> getItems() const;

    // Passage management
    void addPassage(const std::string &, std::shared_ptr<Passage>);
    void removePassage(const std::string &);
    std::shared_ptr<Passage> getPassage(const std::string &);

    // Sanity drain when entering this room
    int getSanityDrain() const;
    void setSanityDrain(int);

protected:
    std::vector<std::shared_ptr<Item>> items;
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
    int sanityDrain = 0;
};

#endif //ZOORK_ROOM_H
