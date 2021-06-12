#ifndef SONG_H
#define SONG_H

#include <QString>
#include <QTextStream>

class Song{
public:
    Song();

    QString getPath() const;
    QString getTitle() const;
    QString getArtist() const;
    int getStartTime() const;
    bool getPlayed() const;

    void setPath(QString);
    void setTitle(QString);
    void setArtist(QString);
    void setStartTime(int);
    void setPlayed(bool);

    bool operator<(const Song&);
    bool operator>(const Song&);
    bool operator==(const Song&);
    Song& operator=(const Song&);

private:
    QString path;
    QString title;
    QString artist;
    int startTime;
    bool played;
};

inline QTextStream& operator<<(QTextStream &out, const Song& t)
{
    out << t.getPath() << Qt::endl << t.getArtist() << Qt::endl <<
           t.getTitle() << Qt::endl << t.getStartTime() << Qt::endl << Qt::endl;
    return out;
}

inline QTextStream& operator>>(QTextStream &in, Song&t)
{
    t.setPath(in.readLine());
    t.setArtist(in.readLine());
    t.setTitle(in.readLine());
    t.setStartTime(in.readLine().toInt());
    return in;
}


#endif // SONG_H
