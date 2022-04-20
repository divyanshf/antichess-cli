#ifndef BOARD_H
#define BOARD_H

#pragma once

class Piece;

#include <vector>
#include <string>
#include "../Pieces/pieces.h"

using namespace std;

// Board
class Board
{
private:
    // Representation
    vector<vector<Piece *>> board;

    // Private Methods
    void displayHorizontalBorder(int n);
    void displayPadding(int n);

public:
    Board();
    ~Board();
    void reset();
    void display();
    vector<vector<Piece *>> &getBoard();
    pair<int, int> getIntCordinates(string pos);
    Piece *getPiece(int row, int col);
    void setPiece(Piece *p, int row, int col);
};
// Constructor
Board::Board()
{
    (this->board).resize(8, vector<Piece *>(8, nullptr));
    this->reset();
}

// Destructor
Board::~Board()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            delete (this->board[i][j]);
    this->board.clear();
}

// Get the board
vector<vector<Piece *>> &Board::getBoard()
{
    return this->board;
}

// Get Cordinates in Integer
pair<int, int> Board::getIntCordinates(string pos)
{
    if (pos.length() != 2)
        return {-1, -1};
    int col = pos[0] - 'A', row = '8' - pos[1];
    return {row, col};
}

// Get the piece at a position
Piece *Board::getPiece(int row, int col)
{
    if (row < 0 || row > 7 || col < 0 || col > 7)
        return nullptr;
    return (this->board)[row][col];
}

// Set piece at a position
void Board::setPiece(Piece *p, int row, int col)
{
    if (row < 0 || row > 7 || col < 0 || col > 7)
    {
        return;
    }
    (this->board)[row][col] = p;
}

// Display Horizontal Border
void Board::displayHorizontalBorder(int n)
{
    cout << "+"
         << " ";
    for (int i = 0; i < n - 2; i++)
        cout << "-"
             << " ";
    cout << "+" << endl;
}

// Display Padding
void Board::displayPadding(int n)
{
    for (int i = 0; i < n; i++)
        cout << " ";
}

// Display Board
void Board::display()
{
    this->displayPadding(4);
    for (char ch = 'A'; ch <= 'H'; ch++)
        cout << ch << " ";
    cout << endl;
    this->displayPadding(2);
    this->displayHorizontalBorder(10);
    for (int i = 0; i < 8; i++)
    {
        cout << (8 - i) << " "
             << "|";
        col::print(" ", 37, 45, 1);
        for (int j = 0; j < 8; j++)
        {
            char rep = (this->board[i][j])->getRep();
            int color = rep == '-' ? 31 : (this->board[i][j])->getColor();
            col::print(rep, color, 45, 1);
            col::print(" ", color, 45, 1);
        }
        cout << "|"
             << " " << (8 - i) << endl;
    }
    this->displayPadding(2);
    this->displayHorizontalBorder(10);
    this->displayPadding(4);
    for (char ch = 'A'; ch <= 'H'; ch++)
        cout << ch << " ";
    cout << endl;
}

// Reset Board
void Board::reset()
{
    // for (int j = 0; j < 8; j++)
    // {
    //     board[1][j] = new Pawn(1, j, false);
    //     board[6][j] = new Pawn(6, j, true);
    // }
    for (int j = 0; j < 2; j++)
    {
        board[0][j * 7] = new Rook(0, j * 7, false);
        board[7][j * 7] = new Rook(7, j * 7, true);
    }
    for (int j = 0; j < 2; j++)
    {
        board[0][j * 5 + 1] = new Knight(0, j * 5 + 1, false);
        board[7][j * 5 + 1] = new Knight(7, j * 5 + 1, true);
    }
    for (int j = 0; j < 2; j++)
    {
        board[0][j * 3 + 2] = new Bishop(0, j * 3 + 2, false);
        board[7][j * 3 + 2] = new Bishop(7, j * 3 + 2, true);
    }
    for (int i = 0; i < 2; i++)
    {
        board[i * 7][3] = new Queen(i * 7, 3, i != 0);
        board[i * 7][4] = new King(i * 7, 4, i != 0);
    }
    for (int i = 1; i < 7; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = new Empty(i, j);
        }
    }
}

#endif