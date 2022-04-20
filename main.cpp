#include <iostream>
#include "./Game/game.h"
using namespace std;

int main()
{
    // Initialize Game
    Game *game = new Game(true, false);

    // Start Game
    game->start();
}