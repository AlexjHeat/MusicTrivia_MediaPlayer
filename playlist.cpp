#include "playlist.h"

Playlist::Playlist(QString name)
{
    this->name = name;
}


bool Playlist::isUpdated()
{
    return updated;
}
