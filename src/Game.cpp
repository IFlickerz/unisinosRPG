#include "../include/Game.h"
#include <iostream>

Game::Game() : student(nullptr), currentScene(nullptr), isGameRunning(false) {}

Game::~Game() {
    delete student;
    delete currentScene;
}

void Game::start() {
    isGameRunning = true;
    while (isGameRunning) {
        mainMenu();
    }
}

void Game::mainMenu() {
    std::cout << "=== UNISINOS RPG ===" << std::endl;
    std::cout << "1. Novo Jogo" << std::endl;
    std::cout << "2. Carregar Jogo" << std::endl;
    std::cout << "3. Créditos" << std::endl;
    std::cout << "4. Sair" << std::endl;

    // Implementar lógica de leitura dos inputs
}

// !!!!
// Restante da implementação
// !!!!