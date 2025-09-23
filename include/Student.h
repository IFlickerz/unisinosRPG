#pragma once
#include "Entity.h"
#include "Item.h"
#include <vector>

class Student : public Entity {
private:
    std::vector<Item*> inventory;
    int treasure; // Grade Points
    int provisions; // Coffees
public:
    // Constructor
    Student(std::string name, int skill, int health, int luck);

    // Destructor - Inventory cleanup
    ~Student();

    // Methods
    bool testAndUseLuck();
    void useProvision();
    void addItem(Item* item);
    void addProvisions(int amount);
    void addTreasure(int amount);
    void displayStatus() const;
};