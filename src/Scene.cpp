#include "Scene.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// Helper to trim whitespace from a string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

Scene::Scene() : itemInScene(nullptr), enemyInScene(nullptr),
                 nextSceneOnVictory(0), nextSceneOnDefeat(0), isFinalScene(false) {}

Scene::~Scene() {
    delete itemInScene;
    delete enemyInScene;
}

bool Scene::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo de cena " << filePath << std::endl;
        return false;
    }

    std::vector<std::string> descriptionLines;
    std::vector<std::string> monsterLines;
    std::vector<std::string> choiceLines;

    std::string line;
    int section = 0; // 0 for description, 1 for monster, 2 for choices

    while (getline(file, line)) {
        std::string trimmed_line = trim(line);
        if (trimmed_line.empty() && section == 0) {
            descriptionLines.push_back("");
            continue;
        }
        if (trimmed_line.empty()) continue;

        if (trimmed_line.rfind('M', 0) == 0 && trimmed_line[1] == ':') {
            section = 1;
        } else if (trimmed_line.rfind('#', 0) == 0) {
            section = 2;
        }

        switch (section) {
            case 0: descriptionLines.push_back(line); break;
            case 1: monsterLines.push_back(trimmed_line); break;
            case 2: choiceLines.push_back(trimmed_line); break;
        }
    }

    // Process Description
    std::stringstream description_stream;
    for (const auto& desc_line : descriptionLines) {
        if (trim(desc_line).rfind('#', 0) == 0) continue;
        if (trim(desc_line) == "FIM") { isFinalScene = true; break; }
        if (trim(desc_line).rfind('I', 0) == 0 && trim(desc_line)[1] == ':') {
            std::stringstream ss(trim(desc_line).substr(2));
            std::string name, type_str, combat_str, fa_str, dmg_str;
            getline(ss, name, ';'); getline(ss, type_str, ';'); getline(ss, combat_str, ';'); getline(ss, fa_str, ';'); getline(ss, dmg_str, ';');
            itemInScene = new Item(trim(name), trim(type_str)[0], std::stoi(combat_str), std::stoi(fa_str), std::stoi(dmg_str));
        } else {
            description_stream << desc_line << "\n";
        }
    }
    descriptionText = description_stream.str();

    // Process Monster
    if (!monsterLines.empty()) {
        std::string monsterName = trim(monsterLines[0].substr(2));
        enemyInScene = new Course(monsterName, 0, 0, 0);

        for (size_t i = 1; i < monsterLines.size(); ++i) {
            const std::string& monster_line = monsterLines[i];
            size_t colonPos = monster_line.find(':');
            if (colonPos == std::string::npos) continue;

            char attr = monster_line[0];

            switch(attr) {
                case 'H':
                case 'E':
                case 'S':
                case 'T':
                case 'P': {
                    std::string value_str = trim(monster_line.substr(colonPos + 1));
                    int value = std::stoi(value_str);
                    if(attr == 'H') enemyInScene->setSkill(value);
                    if(attr == 'E') enemyInScene->setHealth(value);
                    if(attr == 'S') enemyInScene->setLuck(value);
                    if(attr == 'T') enemyInScene->setDrops(value, enemyInScene->getProvisionDrop(), nullptr);
                    if(attr == 'P') enemyInScene->setDrops(enemyInScene->getTreasureDrop(), value, nullptr);
                    break;
                }
                 case 'I': {
                    std::stringstream ss(monster_line.substr(2)); // Pula o "I:"
                    std::string name, type_str, combat_str, fa_str, dmg_str;
                    getline(ss, name, ';'); getline(ss, type_str, ';'); getline(ss, combat_str, ';'); getline(ss, fa_str, ';'); getline(ss, dmg_str, ';');
                    Item* newItem = new Item(trim(name), trim(type_str)[0], std::stoi(combat_str), std::stoi(fa_str), std::stoi(dmg_str));
                    enemyInScene->setDrops(enemyInScene->getTreasureDrop(), enemyInScene->getProvisionDrop(), newItem);
                    break;
                }
                default:
                    if (isdigit(attr)) {
                         nextSceneOnVictory = std::stoi(trim(monster_line.substr(0, colonPos)));
                         nextSceneOnDefeat = std::stoi(trim(monster_line.substr(colonPos + 1)));
                    }
                    break;
            }
        }
    }

    for (const auto& choice_line : choiceLines) {
        size_t colonPos = choice_line.find(':');
        if (colonPos != std::string::npos) {
            int choiceNum = std::stoi(choice_line.substr(1, colonPos - 1));
            choices[choiceNum] = {trim(choice_line.substr(colonPos + 1))};
        }
    }

    file.close();
    return true;
}

void Scene::display() const {
    std::cout << "=================================================\n\n";
    std::cout << descriptionText << "\n";

    if (itemInScene) {
        std::cout << "Você encontrou um item: " << itemInScene->getName() << "!\n\n";
    }

    if (!choices.empty()) {
        std::cout << "O que você faz?\n";
        for (const auto& pair : choices) {
            std::cout << "  " << pair.first << ". " << pair.second.text << "\n";
        }
    }
}

Course* Scene::getEnemy() { return enemyInScene; }
Item* Scene::takeItem() {
    Item* to_return = itemInScene;
    itemInScene = nullptr;
    return to_return;
}

bool Scene::hasChoices() const { return !choices.empty(); }

bool Scene::isCombatScene() const { return enemyInScene != nullptr; }

bool Scene::isEnd() const { return isFinalScene; }

int Scene::getNextScene(bool victory) const { return victory ? nextSceneOnVictory : nextSceneOnDefeat; }

const std::map<int, Choice>& Scene::getChoices() const { return choices; }