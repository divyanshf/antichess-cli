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
    bool turn; //  white->true, black->false

public:
    Game(bool f, bool s);
    ~Game();
    void start();
    void initOptions();
    char showOptions();
    bool makeMove();
};

// Constructor
Game::Game(bool f = true, bool s = false)
{
    // Initialize Players
    this->p1 = new Player(f);
    this->p2 = new Player(s);

    // Setup turn
    this->turn = true;

    // Setup board
    this->b = new Board();

    // Initialize Options
    this->initOptions();
}

// Destructor
Game::~Game()
{
    delete (this->p1);
    delete (this->p2);
    delete (this->b);
    (this->opts).clear();
}

void Game::initOptions()
{
    // Initialize Options
    (this->opts)['Q'] = "Quit";
    (this->opts)['B'] = "Display Board";
    (this->opts)['M'] = "Make A Move";
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
// Returns validity
bool Game::makeMove()
{
    cout << "Enter a move (ex. A4 to B5) : ";
    string move;
    cin >> move;

    // Invalid Format
    if (move.length() != 8)
        return false;

    pair<int, int> from = this->b->getIntCordinates(move.substr(0, 2));
    pair<int, int> to = this->b->getIntCordinates(move.substr(6, 2));

    // Invalid Cordinates
    if (from.first < 0 || from.second < 0 || from.first > 7 || from.second > 7)
        return false;
    if (to.first < 0 || to.second < 0 || to.first > 7 || to.second > 7)
        return false;

    Piece *pFrom = this->b->getPiece(from.first, from.second);

    // Invalid From Piece
    if (!pFrom || pFrom->isWhite() != turn)
        return false;

    Piece *pTo = this->b->getPiece(to.first, to.second);

    // Invalid To Piece
    if (pTo->isWhite() == turn)
        return false;

    // Validity of move according to piece
    bool valid = pFrom->move(pTo);
    if (!valid)
        return false;

    // Moving pFrom to pTo
    this->b->setPiece(pFrom, to.first, to.second);
    this->b->setPiece(nullptr, from.first, from.second);

    // Increase Score for pTo
    if (pTo)
    {
        if (p1->isWhite() != turn)
            p1->incScore(1);
        else
            p2->incScore(1);
        delete (pTo);
    }

    return true;
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