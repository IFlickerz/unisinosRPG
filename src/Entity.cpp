#include "../include/Entity.h"

Entity::Entity(std::string name, int skill, int health, int luck)
    : name(name), skill(skill), currentHealth(health),
      maxHealth(health), currentLuck(luck), maxLuck(luck) {}

void Entity::takeDamage(int damage) {
    this->currentHealth -= damage;
    if (this->currentHealth < 0) {
        this->currentHealth = 0;
    }
}

bool Entity::isAlive() const {
    return this->currentHealth > 0;
}

std::string Entity::getName() const { return this->name; }

int Entity::getSkill() const { return this->skill; }

int Entity::getCurrentHealth() const { return this->currentHealth; }

int Entity::getMaxHealth() const { return this->maxHealth; }

int Entity::getCurrentLuck() const { return this->currentLuck; }