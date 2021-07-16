#include "song.h"
#include <QMessageBox>

Song::Song()
{
    startTime = 0;
}

QString Song::getPath() const { return path; }
QString Song::getTitle() const { return title; }
QString Song::getArtist() const { return artist; }
int Song::getStartTime() const { return startTime; }
bool Song::getPlayed() const {return played; }

void Song::setPath(QString path) { this->path = path; }
void Song::setTitle(QString title) { this->title = title; }
void Song::setArtist(QString artist) { this->artist = artist; }
void Song::setStartTime(int startTime) { this->startTime = startTime; }
void Song::setPlayed(bool played) {this->played = played; }

bool Song::operator<(const Song& other)
{
    QString song1 = this->getArtist() + this->getTitle();
    QString song2 = other.getArtist() + other.getTitle();
    if(song1.compare(song2) < 0)
        return true;
    return false;
}

bool Song::operator>(const Song& other)
{
    QString song1 = this->getArtist() + this->getTitle();
    QString song2 = other.getArtist() + other.getTitle();
    if(song1.compare(song2) > 0)
        return true;
    return false;
}

bool Song::operator==(const Song& other)
{
    bool result{false};
    if(this->path == other.getPath()) result = true;
    return result;
}

Song& Song::operator=(const Song& other)
{
    this->path = other.getPath();
    this->artist = other.getArtist();
    this->title = other.getTitle();
    this->startTime = other.getStartTime();
    return *this;
}
