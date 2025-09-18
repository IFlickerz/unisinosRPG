#pragma once
#include "Student.h"
#include "Scene.h"
#include <vector>

class Game {
private:
    Student* student;
    Scene* currentScene;
    std::vector<int> visitedScenes;
    bool isGameRunning;

    void mainMenu();
    void createNewMenu();
    void loadGame(int slot);
    void saveGame(int slot) const;
    void showCredits() const;
    void mainLoop();
    void processChoice(int sceneId);
    void startCombat();

public:
    // Constructor
    Game();

    // Destructor
    ~Game();

    void start();
};