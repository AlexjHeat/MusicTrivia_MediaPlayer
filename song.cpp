#include "song.h"


QString Song::getPath() const { return path; }
QString Song::getTitle() const { return title; }
QString Song::getArtist() const { return artist; }
int Song::getStartTime() const { return startTime; }

void Song::setPath(QString path) { this->path = path; }
void Song::setTitle(QString title) { this->title = title; }
void Song::setArtist(QString artist) { this->artist = artist; }
void Song::setStartTime(int startTime) { this->startTime = startTime; }
