#include "include/Game.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    // Initializing the game engine
    Game unisinosRPG(argv[0]);

    // Starting exec
    unisinosRPG.start();
    return 0;
}