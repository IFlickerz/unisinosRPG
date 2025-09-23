#include "../include/Game.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

Game::Game(const std::string& exePath) : student(nullptr), currentSceneId(1), isGameRunning(false) {
    rootPath = std::filesystem::path(exePath).parent_path().parent_path();
}

Game::~Game() {
    cleanup();
}

void Game::cleanup() {
    delete student;
    student = nullptr;
}

void Game::start() {
    isGameRunning = true;
    while (isGameRunning) {
        mainMenu();
    }
}

void Game::mainMenu() {
    clearScreen();
    std::cout << "=== UNISINOS RPG ===\n"
              << "1. Novo Jogo\n"
              << "2. Carregar Jogo\n"
              << "3. Créditos\n"
              << "4. Sair\n";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            createNewGame();
            mainLoop();
            break;
        case 2:
            loadGame();
            break;
        case 3:
            showCredits();
            break;
        case 4:
            isGameRunning = false;
            break;
        default:
            std::cout << "Opção inválida, selecione uma das opções disponíveis.\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
    }
}

void Game::createNewGame() {
    cleanup();
    clearScreen();
    std::string name;
    std::cout << "Digite o nome do estudante: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, name);

    int totalPoints, skill, health, luck, points;

    std::cout << "Atributos iniciais: Habilidade(6), Saúde(12), Sorte(6)\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    do {
        totalPoints = 12;
        skill = 6, health = 12, luck = 6;

        std::cout << "\nVocê tem " << totalPoints << " pontos para distribuir entre Habilidade, Saúde e Sorte.\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        do {
            std::cout << "Pontos para por em Habilidade (atual 6, max 12): ";
            std::cin >> points;
        } while (points < 0 || points > totalPoints || skill + points > 12);
        skill += points;
        totalPoints -= points;

        do {
            std::cout << "Pontos para por em Saúde (atual 12, max 24): ";
            std::cin >> points;
        } while (points < 0 || points > totalPoints || health + points > 24);
        health += points;
        totalPoints -= points;

        if (totalPoints > 0) {
            luck += totalPoints;
            if (luck > 12) { luck = 12; }
            std::cout << "Os " << totalPoints << " pontos restantes foram colocados em Sorte.\n";
        }

        int choice;
        do {
            std::cout << "Distribuição de pontos correta?\n"
                      << "1. Sim\n"
                      << "2. Refazer\n";
            std::cin >> choice;
        } while (choice != 1 && choice != 2);

        if (choice == 1) break;
    } while (true);

    student = new Student(name, skill, health, luck);
    currentSceneId = 1;
}

void Game::mainLoop() {
    while (isGameRunning && student->isAlive()) {
        Scene currentScene;

        if (auto scenePath = rootPath / "data" / "scenes" / (std::to_string(currentSceneId) + ".txt"); 
            !currentScene.loadFromFile(scenePath.string())) {
            std::cerr << "Falha critica: O arquivo de cena nao pode ser carregado. Verifique o caminho.\n";
            break;
        }

        saveGame(); // salva automaticamente a cada cena

        clearScreen();
        student->displayStatus();
        currentScene.display();

        if (currentScene.isEnd()) {
            std::cout << "\n--- O FIM --- \n";
            isGameRunning = false;
            break;
        }

        if (Item* item = currentScene.takeItem()) {
            std::cout << "Voce pegou: " << item->getName() << ".\n";
            student->addItem(item);
        }

        if (currentScene.isCombatScene()) {
            std::cout << "\nUm inimigo aparece! Pressione Enter para iniciar o combate...";
            std::cin.get();
            startCombat(&currentScene);
        } else if (currentScene.hasChoices()) {
            std::cout << "\nDigite a sua escolha: ";
            int choice;
            std::cin >> choice;

            while (std::cin.fail() || currentScene.getChoices().find(choice) == currentScene.getChoices().end()) {
                std::cout << "Escolha invalida. Tente novamente: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> choice;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (choice == 999) { isGameRunning = false; }
            else { currentSceneId = choice; }
        } else {
            std::cout << "\nPressione Enter para continuar...\n";
            std::cin.get();
        }
    }

    if (!student->isAlive()) {
        std::cout << "\n--- GAME OVER ---\n";
    }

    if (!isGameRunning) {
        std::cout << "\nPressione Enter para retornar ao menu principal...\n";
        if (std::cin.peek() == '\n') std::cin.ignore();
        std::cin.get();
    }
}

void Game::startCombat(Scene* scene) {
    Course* enemy = scene->getEnemy();

    while (student->isAlive() && enemy->isAlive()) {
        clearScreen();
        student->displayStatus();
        std::cout << "--- Inimigo: " << enemy->getName() << " ---\n"
                  << "  Saude: " << enemy->getCurrentHealth() << " / " << enemy->getMaxHealth() << "\n"
                  << "------------------------\n\n";

        std::cout << "Escolha sua acao para esta rodada:\n";
        std::cout << "1. Atacar Normalmente (disputa de FA)\n";
        std::cout << "2. Tentar a Sorte (custa 1 ponto de Sorte)\n";
        std::cout << "Escolha uma opcao: ";

        int choice;
        std::cin >> choice;
        while (std::cin.fail() || (choice != 1 && choice != 2)) {
            std::cout << "Escolha invalida. Tente novamente: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> choice;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            int playerFA = student->calculateAttackForce();
            int enemyFA = enemy->calculateAttackForce();
            std::cout << "\nSua Força de Ataque: " << playerFA << " | Força de Ataque do Inimigo: " << enemyFA << "\n";

            if (playerFA > enemyFA) {
                enemy->takeDamage(2);
                std::cout << "Você acertou! A saúde do inimigo agora é " << enemy->getCurrentHealth() << ".\n";
            } else if (enemyFA > playerFA) {
                student->takeDamage(2);
                std::cout << "O inimigo acertou! A sua saúde agora é " << student->getCurrentHealth() << ".\n";
            } else {
                std::cout << "Empate! Ninguem acertou.\n";
            }
        } else if (choice == 2) {
            if (student->getCurrentLuck() > 0) {
                std::cout << "\nVocê testa a sua sorte... (Sorte atual: " << student->getCurrentLuck() << ")\n";
                bool lucky = student->testAndUseLuck(); // Decrements luck by 1

                if (lucky) {
                    std::cout << "SORTUDO! O seu ataque é crítico!\n";
                    enemy->takeDamage(4);
                    std::cout << "Você causou 4 de dano! A saúde do inimigo agora é " << enemy->getCurrentHealth() << ".\n";
                } else {
                    std::cout << "AZARADO! O seu ataque sai pela culatra!\n";
                    student->takeDamage(1);
                    std::cout << "Voce tropeçou e sofreu 1 de dano. Sua saúde agora é " << student->getCurrentHealth() << ".\n";
                }
            } else {
                std::cout << "\nVocê nao tem pontos de Sorte restantes!\n";
                std::cout << "Realizando um ataque normal...\n";

                int playerFA = student->calculateAttackForce();
                int enemyFA = enemy->calculateAttackForce();

                std::cout << "Sua Força de Ataque: " << playerFA << " | Forçaa de Ataque do Inimigo: " << enemyFA << "\n";

                if (playerFA > enemyFA) {
                    enemy->takeDamage(2);
                    std::cout << "Você acertou! A saúde do inimigo agora é " << enemy->getCurrentHealth() << ".\n";
                } else {
                    std::cout << "O inimigo acertou! A sua saúde agora é " << student->getCurrentHealth() << ".\n";
                }
            }
        }

        std::cout << "---------------------------------\n";
        std::cout << "Pressione Enter para continuar...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    if (student->isAlive()) {
        std::cout << "Você derrotou " << enemy->getName() << "!\n";

        int treasure = enemy->getTreasureDrop();
        int provisions = enemy->getProvisionDrop();
        Item* droppedItem = enemy->getItemDrop();

        if(treasure > 0) student->addTreasure(treasure);
        if(provisions > 0) student->addProvisions(provisions);
        if (droppedItem) {
            std::cout << "Você recebeu " << droppedItem->getName() << "!\n";
            student->addItem(droppedItem);
        }

        currentSceneId = scene->getNextScene(true);
    } else {
        currentSceneId = scene->getNextScene(false);
    }

    std::cout << "Pressione Enter para continuar...";
    std::cin.get();
}

void Game::loadGame() {
    cleanup(); 

    std::ifstream saveFile(rootPath / "savegame.txt");
    if (!saveFile.is_open()) {
        std::cerr << "Nenhum save encontrado.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    std::string name;
    std::getline(saveFile, name);

    int skill, curHealth, maxHealth, curLuck, maxLuck;
    saveFile >> skill >> curHealth >> maxHealth >> curLuck >> maxLuck;

    int treasure, provisions;
    saveFile >> treasure >> provisions;

    saveFile >> currentSceneId;

    
    student = new Student(name, skill, maxHealth, maxLuck);
    student->setCurrentHealth(curHealth);
    student->setCurrentLuck(curLuck);
    student->addTreasure(treasure);
    student->addProvisions(provisions);

    
    int itemCount;
    saveFile >> itemCount;
    saveFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    for (int i = 0; i < itemCount; i++) {
        std::string itemName;
        std::getline(saveFile, itemName);
        student->addItem(new Item(itemName));
    }

    saveFile.close();

    std::cout << "Jogo carregado com sucesso!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    mainLoop();
}

void Game::saveGame() {
    if (!student) return; 
    
    std::ofstream saveFile(rootPath / "savegame.txt");
    if (!saveFile.is_open()) {
        std::cerr << "Erro ao salvar o jogo.\n";
        return;
    }

    saveFile << student->getName() << "\n";
    saveFile << student->getSkill() << " "
             << student->getCurrentHealth() << " "
             << student->getMaxHealth() << " "
             << student->getCurrentLuck() << " "
             << student->getMaxLuck() << "\n";
    saveFile << student->getTreasure() << " "
             << student->getProvisions() << "\n";

    saveFile << currentSceneId << "\n";

    auto items = student->getInventory();
    saveFile << items.size() << "\n";
    for (auto* item : items) {
        saveFile << item->getName() << "\n";
    }

    saveFile.close();
    std::cout << "Jogo salvo com sucesso!\n";
}

void Game::showCredits() const {
    clearScreen();
    std::cout << "--- Créditos ---\n\n"
              << "  Um jogo desenvolvido por:\n"
              << "   - Nicolas Mossmann Lemos\n"
              << "   - Lucas Calsing\n\n"
              << "  Para a disciplina de Algoritmos e Programação: Orientação a Objetos\n"
              << "  Universidade do Vale do Rio dos Sinos - UNISINOS\n\n";

    std::cout << "Pressione Enter para retornar ao menu principal...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
