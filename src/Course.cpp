#include "../include/Course.h"
#include <random>

Course::Course(std::string name, int skill, int health, int luck, bool allowsFleeing)
    : Entity(std::move(name), skill, health, luck), allowsFleeing(allowsFleeing),
        treasureDrop(0), provisionDrop(0), itemDrop(nullptr) {}

Course::~Course() {
    delete itemDrop;
}

void Course::setDrops(int treasure, int provisions, Item* item) {
    this->treasureDrop = treasure;
    this->provisionDrop = provisions;
    this->itemDrop = item;
}

int Course::getTreasureDrop() const { return this->treasureDrop; }
int Course::getProvisionDrop() const { return this->provisionDrop; }

// Transfer items (course -> student)
Item* Course::getItemDrop() {
    Item* to_return = itemDrop;
    itemDrop = nullptr;
    return to_return;
}