#include "../include/Scene.h"
#include <fstream>
#include <sstream>
#include <iostream>

Scene::Scene() : itemInScene(nullptr), enemyInScene(nullptr), nextSceneOnDefeat(0), nextSceneOnVictory(0) {}

Scene::~Scene() {
    delete itemInScene;
    delete enemyInScene;
}

bool Scene::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de cena: " << filePath << std::endl;
        return false;
    }

    // !!!!
    // Falta criar a lógica pra leitura do arquivo
    // !!!!

    file.close();
    return true;
}

// !!!!
// Falta os getters
// !!!!