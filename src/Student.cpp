#include "../include/Student.h"
#include <iostream>
#include <random>

Student::Student(std::string name, int skill, int health, int luck)
    : Entity(name, skill, health, luck), treasure(0), provisions(2) {}

Student::~Student() {
    for (Item* item : inventory) {
        delete item;
    }
    inventory.clear();
}

int Student::calculateAttackForce() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1,10);

    return distrib(gen) + this->skill;
}

void Student::useProvision() {
    if (provisions > 0) {
        this->currentHealth += 4; // A Coffee restores 4 health

        if (this->currentHealth > this->maxHealth) {
            this->currentHealth = this->maxHealth;
        }

        this->provisions--;
        std::cout << "Você tomou um café e recuperou 4 pontos mentais de vida" << std::endl;
    }
}

// !!!!
// Implementar ainda os métodos de testLuck, addItem e displayInventory
// !!!!