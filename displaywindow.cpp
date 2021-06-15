#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);


    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setVideoOutput(ui->VideoOutput);

}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::play(QString fileName, int startTime)
{
    mediaPlayer->setMedia(QUrl::fromLocalFile(fileName));
    mediaPlayer->setPosition(startTime * 1000);
    mediaPlayer->play();
}

void DisplayWindow::stop()
{
    mediaPlayer->stop();
}

void DisplayWindow::setVolume(int v)
{
    volume = v;
    mediaPlayer->setVolume(v);
}

void DisplayWindow::revealVideo()
{
   ui->VideoOutput->show();
}

void DisplayWindow::hideVideo()
{
    ui->VideoOutput->hide();
}

void DisplayWindow::clockDisplay(int n)
{
    ui->clock->display(n);
}
