#pragma once
#include <string>

class Item {
private:
    std::string name;
    char type; // w (weapon) / r (armor) / c (common)
    bool usableInCombat;
    int bonusAF, bonusDamage;

public:
    // Constructor
    Item(std::string name, char type, bool combat, int af, int damage);

    // Destructor
    ~Item() = default;

    // Getters
    std::string getName() const;
    char getType() const;
};