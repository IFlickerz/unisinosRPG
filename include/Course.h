#pragma once
#include "Entity.h"
#include "Item.h"

class Course : public Entity {
private:
    bool allowsFleeing; // Drop out the course
    int treasureDrop, provisionDrop;
    Item* itemDrop;

public:
    // Constructor
    Course(std::string name, int skill, int health, int luck, bool allowsFleeing = true);

    // Destructor
    ~Course();

    void setDrops(int treasure, int provisions, Item* item);
    int getTreasureDrop() const;
    int getProvisionDrop() const;
    Item* getItemDrop();
};