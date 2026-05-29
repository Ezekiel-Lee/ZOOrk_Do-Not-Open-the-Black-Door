//
// Created by Richard Skarbez on 5/7/23.
// Modified for Cthulhu Mythos theme.
//

#include "../header/Character.h"

Character::Character(const std::string &n, const std::string &d) : GameObject(n, d) {}

void Character::addItem(std::shared_ptr<Item> item) {
    inventory.push_back(std::move(item));
}

void Character::removeItem(const std::string &itemName) {
    auto it = std::find_if(inventory.begin(), inventory.end(),
        [&itemName](const std::shared_ptr<Item> &item) {
            return item->getName() == itemName;
        });
    if (it != inventory.end()) {
        inventory.erase(it);
    }
}

std::shared_ptr<Item> Character::getItem(const std::string &itemName) const {
    for (const auto &item : inventory) {
        if (item->getName() == itemName) return item;
    }
    return nullptr;
}

std::vector<std::shared_ptr<Item>> Character::getInventory() const {
    return inventory;
}

bool Character::hasItem(const std::string &itemName) const {
    return getItem(itemName) != nullptr;
}
