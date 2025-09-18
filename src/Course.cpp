#include "../include/Course.h"
#include <random>

Course::Course(std::string name, int skill, int health, int luck, bool allowsFleeing)
    : Entity(name, skill, health, luck), allowsFleeing(allowsFleeing) {}

int Course::calculateAttackForce() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1,10);

    return distrib(gen) + this->skill;
}
