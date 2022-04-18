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

public:
    Game();
    Game(vector<vector<int>> &state);
    void initPieceMap();
    void displayBoard();
};

// Constructor
Game::Game()
{
    initPieceMap();
    board.resize(8, vector<int>(8, 0));

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
    initPieceMap();
    board = state;
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

    cout << "+"
         << " ";
    for (int j = 0; j < 8; j++)
        cout << "-"
             << " ";
    cout << "+" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << "|"
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
    cout << "+"
         << " ";
    for (int j = 0; j < 8; j++)
        cout << "-"
             << " ";
    cout << "+" << endl;

    for (char ch = 'A'; ch <= 'H'; ch++)
    {
        cout << ch << " ";
    }
    cout << endl;
    cout << "WHITE" << endl;
}

#endif