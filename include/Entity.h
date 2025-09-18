#pragma once
#include <string>

// Base class to represent any alive entity (student & course)
class Entity {
protected:
    std::string name;
    int skill, currentHealth, maxHealth, currentLuck, maxLuck;

public:
    // Constructor
    Entity(std::string name, int skill, int health, int luck);

    // Virtual Destructor to avoid memory leak
    virtual ~Entity() = default;

    // Combat & Status methods
    void takeDamage(int damage);
    bool isAlive() const;

    // Getters
    std::string getName() const;
    int getSkill() const;
    int getCurrentHealth() const;
    int getMaxHealth() const;
    int getCurrentLuck() const;

    // Virtual method for calculate attack in child classes
    virtual int calculateAttackForce() const = 0;

};