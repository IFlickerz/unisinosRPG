#pragma once
#include "Student.h"
#include "Scene.h"
#include <filesystem>

class Game {
private:
    Student* student;
    int currentSceneId;
    bool isGameRunning;
    std::filesystem::path rootPath;

    void mainMenu();
    void createNewGame();
    void mainLoop();

    void loadGame();
    void saveGame(); // Should be called auto when a new scene loads in

    void showCredits() const;

    void startCombat(Scene* scene);
    void cleanup();

public:
    // Constructor
    explicit Game(const std::string& exePath);

    // Destructor
    ~Game();

    void start();
};