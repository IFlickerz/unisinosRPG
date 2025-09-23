#include "../include/Student.h"
#include <iostream>
#include <random>

Student::Student(std::string name, int skill, int health, int luck)
    : Entity(std::move(name), skill, health, luck), treasure(0), provisions(2) {}

Student::~Student() {
    for (Item* item : inventory) {
        delete item;
    }
    inventory.clear();
}

bool Student::testAndUseLuck() {
    if (currentLuck <= 0) return false;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1,6);

    bool success = (distrib(gen) + distrib(gen)) <= currentLuck;
    currentLuck--;

    return success;
}

void Student::useProvision() {
    if (provisions > 0) {
        this->currentHealth += 4; // A Coffee restores 4 health

        if (this->currentHealth > this->maxHealth) {
            this->currentHealth = this->maxHealth;
        }

        this->provisions--;
        std::cout << "Você tomou um café e recuperou 4 pontos mentais de vida" << std::endl;
    } else {
        std::cout << "Você está sem nenhum café" << std::endl;
    }
}

void Student::addItem(Item* item) {
    if (item) {
        inventory.push_back(item);
    }
}

void Student::addProvisions(int amount) { this->provisions += amount; }
void Student::addTreasure(int amount) { this->treasure += amount; }

void Student::displayStatus() const {
    std::cout << "--- Status de " << name << " ---\n"
              << "  Saúde Mental: " << currentHealth << " / " << maxHealth << "\n"
              << "  Habilidade: " << skill << "\n"
              << "  Sorte: " << currentLuck << " / " << maxLuck << "\n"
              << "  Cafés: " << provisions << "\n"
              << "  Tesouro: " << treasure << "\n"
              << "  Inventário: ";
    if (inventory.empty()) {
        std::cout << "Vazio\n";
    } else {
        for (size_t i = 0; i < inventory.size(); i++) {
            std::cout << inventory[i]->getName() << (i == inventory.size() - 1 ? "" : ", ");
        }
        std::cout << "\n";
    }
    std::cout << "------------------------\n\n";
}