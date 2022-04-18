// Include Guards
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "color.h"
#include "player.h"

using namespace std;

// Game Class
class Game
{
private:
    // White -> (+)ve
    // Black -> (-)ve
    vector<vector<int>> board;

    // Map integers to pieces
    unordered_map<int, char> pieceMap;

    // Current Player
    int turn = 0;

    // Players
    Player *p1, *p2;

    // Player Options
    vector<string> strOptions;
    enum options
    {
        Q = 3,
        D = 1,
        M = 2
    };

public:
    Game();
    Game(vector<vector<int>> &state);
    void start();
    void reset();
    void init();
    void initPieceMap();
    void displayBoard();
    void changeTurn();
    void makeMove();
    int selectOption();
};

// Constructor
Game::Game()
{
    this->init();
    this->reset();

    // Placing the pawns
    for (int j = 0; j < 8; j++)
    {
        board[1][j] = -6;
        board[6][j] = 6;
    }

    // Placing the rook, knight and bishop
    for (int j = 0; j < 3; j++)
    {
        board[0][j] = board[0][7 - j] = j - 5;
        board[7][j] = board[7][7 - j] = 5 - j;
    }

    // Placing the king and queen
    board[0][3] = -1;
    board[7][3] = 1;
    board[0][4] = -2;
    board[7][4] = 2;
}

// Constructor with initial state of board
Game::Game(vector<vector<int>> &state)
{
    this->init();
    this->reset();
    board = state;
}

// Initialize Variables
void Game::init()
{
    // Create new players
    p1 = new Player(true);
    p2 = new Player(false);

    this->initPieceMap();

    // Set options
    (this->strOptions).push_back("Display Board");
    (this->strOptions).push_back("Make A Move");
    (this->strOptions).push_back("Quit");
}

// Reset Other Variables
void Game::reset()
{
    this->turn = 1;
    (this->board).resize(8, vector<int>(8, 0));
}

// Start the game
void Game::start()
{
    while (1)
    {
        bool q = false;
        options opt = (options)this->selectOption();
        system("clear");
        switch (opt)
        {
        case Q:
            q = true;
            break;

        case M:
            makeMove();
            break;

        case D:
            this->displayBoard();
            break;

        default:
            break;
        }
        if (q)
            break;
    }
}

// Initialize piece map
void Game::initPieceMap()
{
    pieceMap[0] = '-'; // Empty
    pieceMap[1] = 'K'; // King
    pieceMap[2] = 'Q'; // Queen
    pieceMap[3] = 'B'; // Bishop
    pieceMap[4] = 'N'; // Knight
    pieceMap[5] = 'R'; // Rook
    pieceMap[6] = 'P'; // Pawn
}

// Display Board State
void Game::displayBoard()
{
    cout << "BLACK" << endl;

    for (int i = 0; i < 5; i++)
        cout << " ";

    for (char ch = 'A'; ch <= 'H'; ch++)
    {
        cout << ch << " ";
    }
    cout << endl;
    for (int i = 0; i < 3; i++)
        cout << " ";
    cout << "+"
         << " ";
    for (int j = 0; j < 8; j++)
        cout << "-"
             << " ";
    cout << "+" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << " " << 8 - i << " "
             << "|"
             << " ";
        for (int j = 0; j < 8; j++)
        {
            int color = board[i][j] == 0 ? 31 : board[i][j] > 0 ? 37
                                                                : 30;
            col::printInColor(pieceMap[(abs(board[i][j]))], color, 1);
            cout << " ";
        }
        cout << "|"
             << " " << 8 - i << endl;
    }

    for (int i = 0; i < 3; i++)
        cout << " ";
    cout << "+"
         << " ";
    for (int j = 0; j < 8; j++)
        cout << "-"
             << " ";
    cout << "+" << endl;

    for (int i = 0; i < 5; i++)
        cout << " ";

    for (char ch = 'A'; ch <= 'H'; ch++)
    {
        cout << ch << " ";
    }
    cout << endl;
    cout << "WHITE" << endl;
}

// Change Player Turn
void Game::changeTurn()
{
    turn = -turn;
}

// Make A Move
void Game::makeMove() {}

// Select Option For PLayer
int Game::selectOption()
{
    for (int i = 0; i < (this->strOptions).size(); i++)
    {
        cout << "(" << i + 1 << ")" << (this->strOptions)[i] << endl;
    }
    cout << "Enter the option : ";
    int opt;
    cin >> opt;
    return opt;
}

#endif