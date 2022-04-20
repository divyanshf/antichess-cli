// Include Guards
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

// Player Class
class Player
{
private:
    int score; // Score
    bool white;

public:
    Player(bool w);
    int getScore();
    bool isWhite();
    void setScore(int s);
    void incScore(int val);
};

// Constructor
Player::Player(bool w)
{
    this->score = 0;
    this->white = w;
}

// Is the player white
bool Player::isWhite()
{
    return this->white;
}

// Score getter
int Player::getScore()
{
    return this->score;
}

// Score setter
void Player::setScore(int s)
{
    this->score = s;
}

// Increment PLayer Score
void Player::incScore(int val)
{
    this->score += val;
}
#endif