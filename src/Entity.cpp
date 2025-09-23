#include "../include/Entity.h"

#include <random>

Entity::Entity(std::string name, int skill, int health, int luck)
    : name(std::move(name)), skill(skill), currentHealth(health),
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

void Entity::setHealth(int health) { this->currentHealth = health; this->maxHealth = health; }
void Entity::setSkill(int skill) { this->skill = skill; }
void Entity::setLuck(int luck) { this->currentLuck = luck; this->maxLuck = luck; }

int Entity::calculateAttackForce() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1,10);

    return distrib(gen) + this->skill;
}
