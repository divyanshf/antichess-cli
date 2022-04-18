#include <iostream>
#include "game.h"
using namespace std;

int main()
{
    system("clear");
    Game *game = new Game();
    game->start();
}