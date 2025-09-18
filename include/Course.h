#pragma once
#include "Entity.h"

class Course : public Entity {
private:
    bool allowsFleeing; // Drop out the course

public:
    // Constructor
    Course(std::string name, int skill, int health, int luck, bool allowsFleeing = true);

    // Destructor
    ~Course() = default;

    // Override base class virtual method
    int calculateAttackForce() const override;
};