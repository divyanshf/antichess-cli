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

public:
    Player(bool w);
    bool white;
    int getScore();
    void setScore(int s);
};

// Constructor
Player::Player(bool w)
{
    score = 0;
    white = w;
}

// Score getter
int Player::getScore()
{
    return score;
}

// Score setter
void Player::setScore(int s)
{
    score = s;
}

#endif