#include "player.h"

Player::Player()
{
    name = "";
    score = 0;
}

void Player::setName(QString name) {this->name = name;}
void Player::setScore(int score ) {this->score = score;}
QString Player::getName() {return name;}
int Player::getScore() {return score;}
