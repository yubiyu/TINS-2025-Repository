#include "game.h"

int main(int argc, char **argv) // Apparently the main function must have this signature for cross-platform compatibility
{
    if(!Game::Initialize(argv))
        assert("Initialization error!");

    Game::MainLoop();

    Game::Uninitialize();
    return 0;
}
