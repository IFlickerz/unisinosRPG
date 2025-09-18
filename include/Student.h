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

    // Destructor
    ~Student(); // Inventory cleanup

    // Override base class virtual method
    int calculateAttackForce() const override;

    // Methods
    bool testLuck();
    void useProvision();
    void addItem(Item* item);
    void displayInventory() const;
};