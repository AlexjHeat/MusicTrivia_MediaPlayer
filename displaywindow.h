#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "song.h"


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
    void stop();
    void setVolume(int);

    void revealVideo();
    void hideVideo();
    void clockDisplay(int);

private:
    Ui::DisplayWindow *ui;
    QMediaPlayer* mediaPlayer;
    Song currentlyPlaying;
    int volume;


};

#endif // DISPLAYWINDOW_H
