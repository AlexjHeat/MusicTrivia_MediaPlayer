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

void DisplayWindow::setScoreboard(Player* playerList, int playerCount)
{
    int count = ui->scoreboardLayout->count();
    for(int i = 0; i < count; i++)
    {
        ui->scoreboardLayout->removeWidget(arr[i]);
        delete arr[i];
    }

    delete arr;
    arr = new QLabel*[playerCount];
    for(int i = 0; i < playerCount; i++)
    {
        arr[i] = new QLabel;
        QString spacing = ":\t";
        if (playerList[i].getName().length() <= 8)
            spacing += "\t";

        arr[i]->setText(playerList[i].getName() + spacing + QString::number(playerList[i].getScore()));

        int column = i%4;
        int row = i/4;

        ui->scoreboardLayout->addWidget(arr[i], row, column);
    }
}
