#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
public:
    Player();
    void setName(QString);
    void setScore(int);
    QString getName();
    int getScore();

private:
    QString name;
    int score;
};

#endif // PLAYER_H
