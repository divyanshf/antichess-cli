// Include Guards
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "../color.h"
#include "../Player/player.h"
#include "../Board/board.h"
#include "../Pieces/pieces.h"

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
    void changeTurn();
    bool makeMove();
    void displayScores();
    bool isEnd();
};

// Constructor
Game::Game(bool f = true, bool s = false)
{
    // Initialize Players
    this->p1 = new Player(f);
    this->p2 = new Player(s);

    // Setup turn
    this->turn = f;

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

// Change Turn
void Game::changeTurn()
{
    this->turn = !this->turn;
}

// Display Scores
void Game::displayScores()
{
    col::print("Scores\n", 32, 1);
    string text = "Player 1 : " +
                  to_string(this->p1->getScore()) +
                  "\nPlayer 2 : " + to_string(this->p2->getScore()) +
                  "\n";
    col::print(text, 32, 1);
}

// Has the game ended
bool Game::isEnd()
{
    bool found1 = false, found2 = false;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece *p = this->b->getPiece(i, j);
            if (p->isEmpty() == true)
                continue;
            if (p->isWhite() == this->turn)
                found1 = true;
            else if (p->isWhite() != this->turn)
                found2 = true;
        }
    }
    // If a piece for one player does not exist
    if (!found1 || !found2)
        return true;

    return false;
}

// Make a move
// Returns validity
bool Game::makeMove()
{
    cout << "Enter a move (ex. A4 to B5) : " << endl;
    string move;
    getline(cin, move);

    // Invalid Format
    if (move.length() != 8)
        return false;

    pair<int, int> from = this->b->getIntCordinates(move.substr(0, 2));
    pair<int, int> to = this->b->getIntCordinates(move.substr(6, 2));

    // Invalid Cordinates
    if (from.first == to.first && from.second == to.second)
        return false;
    if (from.first < 0 || from.second < 0 || from.first > 7 || from.second > 7)
        return false;
    if (to.first < 0 || to.second < 0 || to.first > 7 || to.second > 7)
        return false;

    Piece *pFrom = this->b->getPiece(from.first, from.second);

    // Invalid From Piece
    if (pFrom->isEmpty() || pFrom->isWhite() != this->turn)
        return false;

    Piece *pTo = this->b->getPiece(to.first, to.second);

    // Invalid To Piece
    if (!pTo->isEmpty() && pTo->isWhite() == this->turn)
        return false;

    // Validity of move according to piece
    bool valid = pFrom->move(pTo, this->b->getBoard());
    if (!valid)
        return false;

    // Moving pFrom to pTo
    pFrom->setPos(to.first, to.second);
    this->b->setPiece(pFrom, to.first, to.second);
    this->b->setPiece(new Empty(from.first, from.second), from.first, from.second);

    // Increase Score for pTo
    if (pTo->isEmpty() == false)
    {
        if (this->p1->isWhite() != this->turn)
            this->p1->incScore(1);
        else
            this->p2->incScore(1);
        delete (pTo);
    }

    return true;
}

// Start the game
void Game::start()
{
    while (true)
    {
        system("clear");
        bool q = false;
        int winner = 0;
        string curPlayer = this->p1->isWhite() == turn ? "1" : "2"; // True->p1 False->p2
        string info = "Turn : Player " + curPlayer + " (" + (turn ? "WHITE" : "BLACK") + ")";
        col::print(info + "\n", 33, 1);
        char op = this->showOptions();
        system("clear");
        switch (op)
        {
        case 'Q':
        {
            q = true;
            winner = this->p1->isWhite() == turn ? 2 : 1;
            break;
        }

        case 'B':
        {
            this->b->display();
            this->displayScores();
            cout << "Press Enter to continue...";
            cin.get();
            cin.get();

            break;
        }
        case 'M':
        {
            this->b->display();
            this->displayScores();
            col::print(info + "\n", 33, 1);
            cin.get();
            while (true)
            {
                bool valid = this->makeMove();
                if (valid)
                    break;
                col::print("Invalid Move !\n", 31, 1);
            }
            // Check for winning condition
            bool e = this->isEnd();
            if (e)
            {
                q = true;
                int score1 = this->p1->getScore(), score2 = this->p2->getScore();
                winner = score1 == score2 ? 0 : (score1 > score2) ? 1
                                                                  : 2;
            }
            else
            {
                this->changeTurn();
            }
            break;
        }

        default:
            break;
        }

        // If end
        if (q)
        {
            string res = "";
            if (winner != 0)
                res = "Player " + to_string(winner) + " wins!\n";
            else
                res = "Draw !\n";
            col::print(res, 32, 1);
            break;
        }
    }
}

#endif