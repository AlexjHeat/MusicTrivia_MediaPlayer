#include "song.h"


QString Song::getPath() const { return path; }
QString Song::getTitle() const { return title; }
QString Song::getArtist() const { return artist; }
int Song::getStartTime() const { return startTime; }

void Song::setPath(QString path) { this->path = path; }
void Song::setTitle(QString title) { this->title = title; }
void Song::setArtist(QString artist) { this->artist = artist; }
void Song::setStartTime(int startTime) { this->startTime = startTime; }

bool Song::operator<(const Song& other)
{
    bool result{false};
    bool titleCheck{false};

    if(this->getArtist().isEmpty())
    {
        if (other.getArtist().isEmpty())
            titleCheck = true;
    }
    else if(other.getArtist().isEmpty())
            result = true;

    else if(this->getArtist().compare(other.getArtist()) < 0)
        result = true;

    else
        titleCheck = true;

    if (titleCheck)
    {
        if(other.getTitle().isEmpty())
            result = true;
        else if(this->getArtist().compare(other.getArtist()) < 0)
            result = true;
    }
    return result;
}

bool Song::operator>(const Song& other)
{
    bool result{false};
    bool titleCheck{false};

    if(!this->getArtist().isEmpty())
    {
        if (!other.getArtist().isEmpty())
            titleCheck = true;
    }
    else if(!other.getArtist().isEmpty())
            result = true;

    else if(this->getArtist().compare(other.getArtist()) > 0)
        result = true;

    else
        titleCheck = true;

    if (titleCheck)
    {
        if(!other.getTitle().isEmpty())
            result = true;
        else if(this->getArtist().compare(other.getArtist()) > 0)
            result = true;
    }
    return result;
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
