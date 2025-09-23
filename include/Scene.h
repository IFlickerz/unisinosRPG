#pragma once
#include <string>
#include <vector>
#include <map>
#include "Item.h"
#include "Course.h"

struct Choice {
    std::string text;
    std::string requiredItem;
};

class Scene {
private:
    std::string descriptionText;
    std::map<int, Choice> choices;
    Item* itemInScene;
    Course* enemyInScene;
    int nextSceneOnVictory;
    int nextSceneOnDefeat;
    bool isFinalScene;

public:
    // Constructor
    Scene();

    // Destructor
    ~Scene();

    bool loadFromFile(const std::string& filePath);
    void display() const;

    Course* getEnemy();
    Item* takeItem();
    bool hasChoices() const;
    bool isCombatScene() const;
    bool isEnd() const;
    int getNextScene(bool victory) const;
    const std::map<int, Choice>& getChoices() const;
};