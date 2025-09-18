#include "../include/Item.h"

Item::Item(std::string name, char type, bool combat, int af, int damage)
    : name(name), type(type), usableInCombat(combat), bonusAF(af), bonusDamage(damage) {}

std::string Item::getName() const { return this->name; }

char Item::getType() const { return this->type; }