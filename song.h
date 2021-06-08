#ifndef SONG_H
#define SONG_H

#include <QString>

class Song{
public:
    QString getPath();
    QString getTitle();
    QString getArtist();
    int getStartTime();

    void setPath(QString);
    void setTitle(QString);
    void setArtist(QString);
    void setStartTime(int);
private:
    QString path;
    QString title;
    QString artist;
    int startTime;
};

#endif // SONG_H
