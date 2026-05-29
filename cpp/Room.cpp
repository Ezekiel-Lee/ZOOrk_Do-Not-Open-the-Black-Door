//
// Created by Richard Skarbez on 5/7/23.
// Modified for Cthulhu Mythos theme.
//

#include "../header/NullPassage.h"
#include "../header/Room.h"

#include <utility>
#include <iostream>

Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(std::move(item));
}

void Room::removeItem(const std::string &itemName) {
    auto it = std::find_if(items.begin(), items.end(),
        [&itemName](const std::shared_ptr<Item> &item) {
            return item->getName() == itemName;
        });
    if (it != items.end()) {
        items.erase(it);
    }
}

std::shared_ptr<Item> Room::getItem(const std::string &itemName) {
    for (auto &item : items) {
        if (item->getName() == itemName) return item;
    }
    return nullptr;
}

std::vector<std::shared_ptr<Item>> Room::getItems() const {
    return items;
}

int Room::getSanityDrain() const {
    return sanityDrain;
}

void Room::setSanityDrain(int drain) {
    sanityDrain = drain;
}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    auto it = passageMap.find(direction);
    if (it != passageMap.end()) {
        passageMap.erase(it);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    auto it = passageMap.find(direction);
    if (it != passageMap.end()) {
        return it->second;
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}
