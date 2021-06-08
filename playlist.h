#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>

const int MAX_SIZE = 500;
class Playlist{
public:
    Playlist(QString);
    bool isUpdated();

private:
    QString name;
    bool updated;
};

#endif // PLAYLIST_H
