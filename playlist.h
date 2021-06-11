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
    Playlist();
    Playlist(QString);

    QString getName();
    void setName(QString);

    bool getChanged();
    void setChanged(bool);

    void add(QString);
    void remove(int);
    void sort();

    void save();
    void load(QFile&);
    QStringList getList();



private:
    QString name;
    Song list[MAX_SIZE];
    int n;
    bool changed;
};

#endif // PLAYLIST_H
