#include "Game.hpp"

int main(int  /*argc*/, char** argv)
{
    Game game{argv[0]};

    while (game.isRunning())
        game.gameLoop();

    return 0;
}