#include <iostream>
#include "./Game/game.h"
using namespace std;

int main()
{
    system("clear");

    // Initialize Game
    Game *game = new Game(true, false);

    // Start Game
    game->start();
}