#include "displaywindow.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayWindow)
{
    ui->setupUi(this);

    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setVideoOutput(ui->VideoOutput);
    // Last ditch plan if I can't find another solution. Destroy mediaPlayer everytime a song is stopped.  Create new mediaPlayer object when song is played.  Set video output in revealVideo()
        // Create new media player at this->play()
        // Set Video Output at this->revealVideo()
        // Destroy media player at this->hideVideo()

    volUpTimer = new QTimer;
    volDownTimer = new QTimer;

    connect(volUpTimer, SIGNAL(timeout()), this, SLOT(volumeUp()));
    connect(volDownTimer, SIGNAL(timeout()), this, SLOT(volumeDown()));

    arrName = new QLabel*[12];
    arrScore = new QLabel*[12];

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
    volUpTimer->start(7);
    mediaPlayer->setVolume(0);
    volDownTimer->stop();

}

void DisplayWindow::resume()
{
    mediaPlayer->play();
    volUpTimer->start(7);
    mediaPlayer->setVolume(0);
    volDownTimer->stop();
}

void DisplayWindow::pause()
{
    volUpTimer->stop();
    volDownTimer->start(7);
}

void DisplayWindow::stop()
{
    volUpTimer->stop();
    volDownTimer->start(7);
    this->hideVideo();
}

void DisplayWindow::setVolume(int v)
{
    volume = v;
    mediaPlayer->setVolume(volume);
}

void DisplayWindow::revealVideo()
{
   ui->VideoOutput->show();
   ui->clock->hide();
   ui->revealLabel->setText(this->currentlyPlaying.getTitle());

}

void DisplayWindow::hideVideo()
{
    ui->VideoOutput->hide();
    ui->clock->show();
    ui->revealLabel->setText("");
}

void DisplayWindow::setClock(int n)
{
    ui->clock->display(n);
}

void DisplayWindow::setScoreboard(Player* playerList, int playerCount)
{
    int count = ui->scoreLayout->count();

    if(arrName != NULL)
    {
        for(int i = 0; i < count; i++)
        {
            ui->nameLayout->removeWidget(arrName[i]);
            ui->scoreLayout->removeWidget(arrScore[i]);
            delete arrName[i];
            delete arrScore[i];
        }
    }


    for(int i = 0; i < playerCount; i++)
    {
        arrName[i] = new QLabel;
        arrScore[i] = new QLabel;

        arrName[i]->setText(playerList[i].getName());
        arrScore[i]->setText(QString::number(playerList[i].getScore()));

        arrName[i]->setStyleSheet("font: open sans; font-size: 24px; font-color: #f9f4ef; font-weight: bold;");
        arrScore[i]->setStyleSheet("font: open sans; font-size: 24px; font-color: #f9f4ef; font-weight: bold;");
        ui->nameLayout->addWidget(arrName[i]);
        ui->scoreLayout->addWidget(arrScore[i]);
    }
}

void DisplayWindow::volumeUp()
{
    int currentVolume = mediaPlayer->volume();
    if(currentVolume < volume)
        mediaPlayer->setVolume(currentVolume + 1);
    else
        volUpTimer->stop();
}

void DisplayWindow::volumeDown()
{
    int currentVolume = mediaPlayer->volume();
    if(currentVolume > 0)
        mediaPlayer->setVolume(currentVolume - 1);
    else
    {
        mediaPlayer->pause();
        volDownTimer->stop();
    }
}

void DisplayWindow::setRevealLabel(QString text)
{
    ui->revealLabel->setText(text);
}
