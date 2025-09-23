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

    void Game::mainMenu() {
    std::cout << "\n=== UNISINOS RPG ===\n";
    std::cout << "1. Novo Jogo\n2. Carregar Jogo\n3. Créditos\n4. Sair\n";
    std::cout << "Escolha: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1: createNewMenu(); break;
        case 2: loadGame(1); break; 
        case 3: showCredits(); break;
        case 4: isGameRunning = false; break;
        default: std::cout << "Opção inválida!\n";
    }
}

void Game::createNewMenu() {
    std::string name;
    std::cout << "Digite o nome do seu estudante: ";
    std::cin >> name;

    student = new Student(name, 10, 50, 5);
    currentScene = new Scene(1, "Você está no campus. Escolha seu caminho.", false);

    mainLoop();
}

void Game::loadGame(int slot) {
    std::cout << "Carregando jogo do slot " << slot << "...\n";

    student = new Student("AlunoCarregado", 12, 40, 6);
    currentScene = new Scene(1, "Cena carregada", false);
    mainLoop();
}

void Game::saveGame(int slot) const {
    std::cout << "Jogo salvo no slot " << slot << "!\n";
}

void Game::showCredits() const {
    std::cout << "\n=== CRÉDITOS ===\n";
    std::cout << "Desenvolvedores: Lucas e Nicolas\n";
    std::cout << "Versão: 0.1\n";
}
}

// !!!!
// Restante da implementação
// !!!!