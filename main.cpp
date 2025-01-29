#include "Game.hpp"
#include <iostream>

int main()
{
    Game game;
    game.loadResources();

    while (game.isRunning())
        game.gameLoop();

    return 0;
}