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

public:
    // Constructor
    Scene();

    // Destructor
    ~Scene();

    bool loadFromFile(const std::string& filePath);

    std::string getText() const;
    const std::map<int, Choice>& getChoices() const;
    Course* getEnemy() const;
};