#include "Game.hpp"
#include <iostream>

int main()
{
    Game game;
    if (!game.loadResources())
    {
        std::cout << "Could not load required resources\n";
        return 1;
    }

    while (game.isRunning())
        game.gameLoop();

    return 0;
}