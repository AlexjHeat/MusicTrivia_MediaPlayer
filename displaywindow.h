#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QLabel>
#include "song.h"
#include "player.h"


namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DisplayWindow(QWidget *parent = nullptr);
    ~DisplayWindow();
    void play(QString fileName, int startTime);
    void resume();
    void pause();
    void stop();

    void revealVideo();
    void hideVideo();
    void setClock(int);
    void setScoreboard(Player*, int);
    void setRevealLabel(QString);

public slots:
    void setVolume(int);

private:
    Ui::DisplayWindow *ui;
    QMediaPlayer* mediaPlayer;
    Song currentlyPlaying;
    int volume;
    int playerCount;
    QLabel** arr;


};

#endif // DISPLAYWINDOW_H
