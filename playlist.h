#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <song.h>

const int MAX_SIZE = 500;
class Playlist{
public:
    Playlist(QString);

    QString getName();
    void setName(QString);

    bool getChanged();
    void setChanged(bool);

    void add(Song);
    void remove(int);

    void save();
    void load(QFile&);


private:
    QString name;
    Song list[MAX_SIZE];
    int n;
    bool changed;
};

#endif // PLAYLIST_H
