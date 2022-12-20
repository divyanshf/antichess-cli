#ifndef PIECES_H
#define PIECES_H

#pragma once

class Board;

#include <iostream>
using namespace std;

// Chess Piece
class Piece
{
private:
    int col;    //  0-7
    int row;    //  0-7
    bool white; // white / black
    int color;  //  Linux Terminal Color
    char rep;   //  Representation on board
    bool empty; //  Is empty cell

public:
    Piece(int r, int c, bool w, bool emp = false)
    {
        this->col = c;
        this->row = r;
        this->white = w;
        this->empty = emp;
        this->color = w ? 37 : 30;
    }

    bool isEmpty()
    {
        return this->empty;
    }

    bool isWhite()
    {
        return this->white;
    }

    // Position Getter
    pair<int, int> getPos()
    {
        return {this->row, this->col};
    }

    // Position Setter
    void setPos(int r, int c)
    {
        this->row = r;
        this->col = c;
    }

    // Representation Getter
    char getRep()
    {
        return this->rep;
    }

    // Representation Setter
    void setRep(char r)
    {
        this->rep = r;
    }

    // Color Getter
    char getColor()
    {
        return this->color;
    }

    // Returns if the move is valid
    virtual bool move(Piece *to, vector<vector<Piece *>> &board)
    {
        return false;
    }
};

// ---------------------------------------------------------------

// Empty
class Empty : public Piece
{
private:
public:
    Empty(int r, int c, bool w = true) : Piece(r, c, w, true)
    {
        this->setRep('-');
    }

    // Pawn Move
    bool move(Piece *to, vector<vector<Piece *>> &board)
    {
        return false;
    }
};

// ---------------------------------------------------------------

// Pawn
class Pawn : public Piece
{
private:
    int dir; // UP=-1 DOWN=1
    bool first;

public:
    Pawn(int r, int c, bool w) : Piece(r, c, w)
    {
        this->setRep('P');
        this->dir = w ? -1 : 1;
        this->first = true;
    }

    // Pawn Move
    bool move(Piece *to, vector<vector<Piece *>> &board)
    {
        if (!to)
            return false;
        pair<int, int> posTo = to->getPos();
        pair<int, int> posFrom = this->getPos();

        // Allowed difference in row and col
        if ((posTo.first - posFrom.first) * this->dir < 0)
            return false;

        if ((!(this->first) && abs(posTo.first - posFrom.first) != 1) || (this->first && abs(posTo.first - posFrom.first) > 2))
            return false;

        // Same Column but destination contains a player.
        if (posFrom.second == posTo.second && to->isEmpty() == false)
            return false;

        if (abs(posFrom.second - posTo.second) == 1 && to->isEmpty())
            return false;

        this->first = false;
        return true;
    }
};

// ---------------------------------------------------------------

// Rook
class Rook : public Piece
{
private:
public:
    Rook(int r, int c, bool w) : Piece(r, c, w)
    {
        this->setRep('R');
    }

    // Rook Move
    bool move(Piece *to, vector<vector<Piece *>> &board)
    {
        if (!to)
            return false;

        pair<int, int> pFrom = this->getPos();
        pair<int, int> pTo = to->getPos();

        // Not in the same col or row
        if (pFrom.first != pTo.first && pFrom.second != pTo.second)
            return false;

        // No piece in same row
        if (pFrom.first == pTo.first)
        {
            int step = pTo.second - pFrom.second > 0 ? 1 : -1;
            bool allEmpty = true;
            for (int i = pFrom.second + step; i != pTo.second; i += step)
            {
                if (board[pFrom.first][i]->isEmpty() == false)
                {
                    allEmpty = false;
                    break;
                }
            }
            if (!allEmpty)
                return false;
        }

        // No piece in same column
        if (pFrom.second == pTo.second)
        {
            int step = pTo.first - pFrom.first > 0 ? 1 : -1;
            bool allEmpty = true;
            for (int i = pFrom.first + step; i != pTo.first; i += step)
            {
                if (board[i][pFrom.second]->isEmpty() == false)
                {
                    allEmpty = false;
                    break;
                }
            }
            if (!allEmpty)
                return false;
        }

        return true;
    }
};

// ---------------------------------------------------------------

// Knight
class Knight : public Piece
{
private:
public:
    Knight(int r, int c, bool w) : Piece(r, c, w)
    {
        this->setRep('N');
    }

    // Knight Move
    bool move(Piece *to, vector<vector<Piece *>> &board)
    {
        if (!to)
            return false;

        pair<int, int> pFrom = this->getPos();
        pair<int, int> pTo = to->getPos();

        // Absolute diff b/w rows is 2 and cols is 1
        if (abs(pFrom.first - pTo.first) == 2 && abs(pFrom.second - pTo.second) == 1)
            return true;

        // Absolute diff b/w rows is 1 and cols is 2
        if (abs(pFrom.second - pTo.second) == 2 && abs(pFrom.first - pTo.first) == 1)
            return true;

        return false;
    }
};

// ---------------------------------------------------------------

// Bishop
class Bishop : public Piece
{
private:
public:
    Bishop(int r, int c, bool w) : Piece(r, c, w)
    {
        this->setRep('B');
    }

    // Bishop Move
    bool move(Piece *to, vector<vector<Piece *>> &board)
    {
        if (!to)
            return false;

        pair<int, int> pFrom = this->getPos();
        pair<int, int> pTo = to->getPos();

        // Slope should be 1 or -1
        int slope = (pFrom.second - pTo.second) / (pFrom.first - pTo.first);
        if (abs(slope) != 1)
            return false;

        // Make i and j steps acc to slope
        int iStep = pTo.first - pFrom.first > 0 ? 1 : -1;
        int jStep = pTo.second - pFrom.second > 0 ? 1 : -1;

        // No piece in between
        bool found = false;
        for (int i = pFrom.first + iStep, j = pFrom.second + jStep;
             i != pTo.first && j != pTo.second;
             i += iStep, j += jStep)
        {
            if (board[i][j]->isEmpty() == false)
            {
                found = true;
                break;
            }
        }
        if (found)
            return false;

        return true;
    }
};

// ---------------------------------------------------------------

// Queen
class Queen : public Piece
{
private:
public:
    Queen(int r, int c, bool w) : Piece(r, c, w)
    {
        this->setRep('Q');
    }

    // Queen Move
    bool move(Piece *to, vector<vector<Piece *>> &board)
    {
        if (!to)
            return false;

        pair<int, int> pFrom = this->getPos();
        pair<int, int> pTo = to->getPos();

        cout << 1;
        // No piece in same row
        if (pFrom.first == pTo.first)
        {
            int step = pTo.second - pFrom.second > 0 ? 1 : -1;
            bool allEmpty = true;
            for (int i = pFrom.second + step; i != pTo.second; i += step)
            {
                if (board[pFrom.first][i]->isEmpty() == false)
                {
                    allEmpty = false;
                    break;
                }
            }
            if (!allEmpty)
                return false;

            return true;
        }

        cout << 2;
        // No piece in same column
        if (pFrom.second == pTo.second)
        {
            int step = pTo.first - pFrom.first > 0 ? 1 : -1;
            bool allEmpty = true;
            for (int i = pFrom.first + step; i != pTo.first; i += step)
            {
                if (board[i][pFrom.second]->isEmpty() == false)
                {
                    cout << i << pFrom.second << endl;
                    allEmpty = false;
                    break;
                }
            }
            if (!allEmpty)
                return false;

            return true;
        }

        // Slope should be 1 or -1
        int slope = (pFrom.second - pTo.second) / (pFrom.first - pTo.first);
        if (abs(slope) != 1)
            return false;

        // Make i and j steps acc to slope
        int iStep = pTo.first - pFrom.first > 0 ? 1 : -1;
        int jStep = pTo.second - pFrom.second > 0 ? 1 : -1;

        cout << 4;
        // No piece in between
        bool found = false;
        for (int i = pFrom.first + iStep, j = pFrom.second + jStep;
             i != pTo.first && j != pTo.second;
             i += iStep, j += jStep)
        {
            if (board[i][j]->isEmpty() == false)
            {
                found = true;
                break;
            }
        }
        if (found)
            return false;

        return true;
    }
};

// ---------------------------------------------------------------

// King
class King : public Piece
{
private:
public:
    King(int r, int c, bool w) : Piece(r, c, w)
    {
        this->setRep('K');
    }

    // King Move
    bool move(Piece *to, vector<vector<Piece *>> &board)
    {
        if (!to)
            return false;

        pair<int, int> pFrom = this->getPos();
        pair<int, int> pTo = to->getPos();

        // Absolute diff b/w rows and cols cannot exceed 1
        if (abs(pFrom.first - pTo.first) <= 1 && abs(pFrom.second - pTo.second) <= 1)
            return true;

        return false;
    }
};

#endif