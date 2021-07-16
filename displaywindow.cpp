#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);



    //Last ditch plan if I can't find another solution.  Destroy mediaPlayer everytime a song is stopped.  Create new mediaPlayer object when song is played.  Set video output in revealVideo()

}

DisplayWindow::~DisplayWindow()
{
    delete ui;
}

void DisplayWindow::play(QString fileName, int startTime)
{
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setMedia(QUrl::fromLocalFile(fileName));
    mediaPlayer->setPosition(startTime * 1000);
    mediaPlayer->play();
}

void DisplayWindow::resume()
{
    mediaPlayer->play();
}

void DisplayWindow::pause()
{
    mediaPlayer->pause();
}

void DisplayWindow::stop()
{
    delete mediaPlayer;
    ui->revealLabel->setText("");
    this->hideVideo();
}

void DisplayWindow::setVolume(int v)
{
    volume = v;
    mediaPlayer->setVolume(v);
}

void DisplayWindow::revealVideo()
{
   mediaPlayer->setVideoOutput(ui->VideoOutput);
   ui->VideoOutput->show();
   ui->clock->hide();
}

void DisplayWindow::hideVideo()
{
    ui->VideoOutput->hide();
    ui->clock->show();
}

void DisplayWindow::setClock(int n)
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
        if (playerList[i].getName().length() <= 9)
            spacing += "\t";

        arr[i]->setText(playerList[i].getName() + spacing + QString::number(playerList[i].getScore()));

        int column = i%4;
        int row = i/4;
        arr[i]->setStyleSheet("font: open sans; font-size: 13px; font-weight: bold;");
        ui->scoreboardLayout->addWidget(arr[i], row, column);
    }
}

void DisplayWindow::setRevealLabel(QString text)
{
    ui->revealLabel->setText(text);
}
