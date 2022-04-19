#ifndef PIECES_H
#define PIECES_H

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

public:
    Piece(int r, int c, bool w)
    {
        this->col = c;
        this->row = r;
        this->white = w;
        this->color = w ? 37 : 30;
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
    virtual bool move(Piece *to)
    {
        return false;
    }
};

// ---------------------------------------------------------------

// Pawn
class Pawn : public Piece
{
private:
    int dir; // UP=1 DOWN=-1

public:
    Pawn(int r, int c, bool w) : Piece(r, c, w)
    {
        this->setRep('P');
        if (w)
            this->dir = 1;
        else
            this->dir = -1;
    }

    // Pawn Move
    bool move(Piece *to)
    {
        return false;
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
    bool move(Piece *to)
    {
        return false;
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
    bool move(Piece *to)
    {
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
    bool move(Piece *to)
    {
        return false;
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
    bool move(Piece *to)
    {
        return false;
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
    bool move(Piece *to)
    {
        return false;
    }
};

#endif