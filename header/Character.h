//
// Created by Richard Skarbez on 5/7/23.
// Modified for Cthulhu Mythos theme.
//

#ifndef ZOORK_CHARACTER_H
#define ZOORK_CHARACTER_H

#include "GameObject.h"
#include "Item.h"
#include <vector>
#include <memory>
#include <memory>
#include <algorithm>

class Character : public GameObject {
public:
    Character(const std::string &, const std::string &);

    // Inventory
    void addItem(std::shared_ptr<Item>);
    void removeItem(const std::string &);
    std::shared_ptr<Item> getItem(const std::string &) const;
    std::vector<std::shared_ptr<Item>> getInventory() const;
    bool hasItem(const std::string &) const;

protected:
    std::vector<std::shared_ptr<Item>> inventory;
};

#endif //ZOORK_CHARACTER_H
