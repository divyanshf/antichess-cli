// Include Guards
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "color.h"
#include "player.h"
#include "board.h"

using namespace std;

// Game Class
class Game
{
private:
    Player *p1, *p2;
    Board *b;
    unordered_map<char, string> opts;

public:
    Game(bool f, bool s);
    void start();
    void init(bool f, bool s);
    char showOptions();
    bool makeMove();
};

// Constructor
Game::Game(bool f = true, bool s = false)
{
    this->init(f, s);
    this->b = new Board();
    this->b->reset();
    this->p1 = p1;
    this->p2 = p2;
}

void Game::init(bool f, bool s)
{
    // Initialize Options
    opts['Q'] = "Quit";
    opts['B'] = "Display Board";
    opts['M'] = "Make A Move";

    // Initialize Players
    p1 = new Player(f);
    p2 = new Player(s);
}

// Show Options
char Game::showOptions()
{
    for (auto o : (this->opts))
    {
        cout << "(" << (o.first) << ")" << (o.second) << endl;
    }
    char choice;
    cin >> choice;
    return choice;
}

// Make a move
bool Game::makeMove()
{
    cout << "Enter a move (ex. A4 to B5) : ";
    string move;
    cin >> move;
    if (move.length() != 8)
        return false;

    pair<int, int> from = this->b->getIntCordinates(move.substr(0, 2));
    pair<int, int> to = this->b->getIntCordinates(move.substr(6, 2));
    if (from.first < 0 || from.second < 0 || from.first > 7 || from.second > 7)
        return false;
    if (to.first < 0 || to.second < 0 || to.first > 7 || to.second > 7)
        return false;
}

// Start the game
void Game::start()
{
    this->b->display();
    while (1)
    {
        char op = this->showOptions();
        bool q = false;
        switch (op)
        {
        case 'Q':
            q = true;
            break;

        case 'B':
            system("clear");
            this->b->display();
            break;

        case 'M':
            while (1)
            {
                bool valid = this->makeMove();
                if (valid)
                    break;
                col::print("Invalid Move !\n", 31, 1);
            }
            break;

        default:
            break;
        }

        if (q)
        {
            break;
        }
    }
}

#endif