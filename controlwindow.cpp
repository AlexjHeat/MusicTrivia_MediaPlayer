#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "playlist.h"


using namespace std;



ControlWindow::ControlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ControlWindow)
    , active(NULL)
    , i(0)
    , currentlyPlaying(false)
{
    ui->setupUi(this);

    listModel = new QStringListModel(this);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->setAlternatingRowColors(true);
    ui->playlistView->setSelectionRectVisible(true);

    display = new DisplayWindow;
    display->setWindowTitle("Display");
    display->show();

    timer = new QTimer(this);
    guessTime = 30;
    ui->lineEditGuessTime->setText(QString::number(guessTime));

    ui->sliderVolume->setRange(0, 100);
    ui->sliderVolume->setValue(100);


    connect(ui->playlistView, SIGNAL(clicked(QModelIndex)), this, SLOT(displaySongData(QModelIndex)));
    connect(ui->lineEditArtist, SIGNAL(textEdited(QString)), this, SLOT(updateArtist(QString)));
    connect(ui->lineEditTitle, SIGNAL(textEdited(QString)), this, SLOT(updateTitle(QString)));
    connect(ui->lineEditStartTime, SIGNAL(textEdited(QString)), this, SLOT(updateStartTime(QString)));
    connect(ui->lineEditGuessTime, SIGNAL(textEdited(QString)), this, SLOT(updateGuessTime(QString)));
    connect(ui->buttonPlay, SIGNAL(released()), this, SLOT(buttonPlay()));
    connect(timer, SIGNAL(timeout()), this, SLOT(countdown()));
    connect(ui->sliderVolume, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
}


ControlWindow::~ControlWindow()
{
    delete ui;
}

void ControlWindow::on_actionLoad_triggered()
{

    if (active != NULL && active->getChanged())
    {
        QMessageBox::StandardButton save = QMessageBox::warning(this, "Unsaved Changes",
                                                                "You have unsaved changes to this playlist, would you like to save them?",
                                                                QMessageBox::Yes | QMessageBox::No);
        if (save == QMessageBox::Yes)
        {
            active->save();
        }
    }

    QString filename = QFileDialog::getOpenFileName(this, tr("Load Playlist"), "", tr("Playlist (*.plt)"));
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Failed to load");
        return;
    }

    if (active != NULL)
        delete active;
    active = new Playlist();
    active->load(file);
    listModel->setStringList(active->getList());
    ui->playlistView->setModel(listModel);
    file.close();
}


void ControlWindow::on_actionSave_triggered()
{
    if(active == NULL)
    {
        QMessageBox::warning(this, "Error", "No active playlist to save");
        return;
    }
    active->save();
}


void ControlWindow::on_actionCreate_triggered()
{
    if (active != NULL && active->getChanged())
    {
        QMessageBox::StandardButton save = QMessageBox::warning(this, "Unsaved Changes",
                                                                "You have unsaved changes to this playlist, would you like to save them?",
                                                                QMessageBox::Yes | QMessageBox::No);
        if (save == QMessageBox::Yes)
        {
            active->save();
        }
    }
    bool ok;
    QString nameInput = QInputDialog::getText(this, "Create new playlist", "Enter a name for the new playlist", QLineEdit::Normal, "playlist_name", &ok);
    if (!ok)
        return;
    if (active != NULL)
        delete active;

    active = new Playlist(nameInput);
    listModel->setStringList(active->getList());
    ui->playlistView->setModel(listModel);
}

void ControlWindow::on_actionAdd_triggered()
{
    if(active == NULL)
     {
         QMessageBox::warning(this, "Error", "No active playlist");
         return;
     }
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "Select a file", "C:\\Users\\Owner\\Music");
    for(int i = 0; i < fileNames.size(); i++)
    {
        active->add(fileNames[i]);
    }
    listModel->setStringList(active->getList());
    ui->playlistView->setModel(listModel);
    active->setChanged(true);
}

void ControlWindow::on_actionRemove_triggered()
{
    if(active == NULL)
     {
         QMessageBox::warning(this, "Error", "No active playlist");
         return;
     }
    active->remove(i);
    listModel->setStringList(active->getList());
    ui->playlistView->setModel(listModel);
    active->setChanged(true);
}

void ControlWindow::on_actionSort_triggered()
{
    if (active == NULL)
    {
        QMessageBox::warning(this, "Error", "No active playlist");
        return;
    }
    active->sort();
    listModel->setStringList(active->getList());
    ui->playlistView->setModel(listModel);
}

void ControlWindow::on_actionRename_triggered()
{
    bool ok;
    QString nameInput = QInputDialog::getText(this, "Rename playlist", "Enter a new name for the playlist", QLineEdit::Normal, active->getName(), &ok);
    if (!ok)
        return;
    active->setName(nameInput);
}

void ControlWindow::displaySongData(QModelIndex t)
{
    i = t.row();
    Song current = active->getSong(i);
    ui->lineEditArtist->setText(current.getArtist());
    ui->lineEditTitle->setText(current.getTitle());
    ui->lineEditStartTime->setText(QString::number(current.getStartTime()));
}

void ControlWindow::updateArtist(QString artist)
{
    active->getSong(i).setArtist(artist);
    listModel->setStringList(active->getList());
    ui->playlistView->setModel(listModel);
    active->setChanged(true);
}

void ControlWindow::updateTitle(QString title)
{
    active->getSong(i).setTitle(title);
    listModel->setStringList(active->getList());
    ui->playlistView->setModel(listModel);
    active->setChanged(true);
}

void ControlWindow::updateStartTime(QString time)
{
    active->getSong(i).setStartTime(time.toInt());
    listModel->setStringList(active->getList());
    ui->playlistView->setModel(listModel);
    active->setChanged(true);
}

void ControlWindow::updateGuessTime(QString time)
{
    guessTime = time.toInt();
}

void ControlWindow::buttonPlay()
{
    if(active->getSong(i).getPath().isEmpty())
    {
        QMessageBox::warning(this, "Error", "No song is selected.");
        return;
    }

    if(!currentlyPlaying)
    {
        Song current = active->getSong(i);
        display->play(current.getPath(), current.getStartTime());
        display->hideVideo();
        currentlyPlaying = true;
        current.setPlayed(true);

        timer->start(1000);
        display->clockDisplay(guessTime);
        ui->clock->display(guessTime);
        ui->buttonPlay->setText("Stop");
        ui->labelCurrent->setText("Currently playing: " + active->getList()[i]);
    }

    else
    {
       display->stop();
       currentlyPlaying = false;
       timer->stop();
       ui->buttonPlay->setText("Play");
    }
}

void ControlWindow::countdown()
{
    int n = ui->clock->intValue() - 1;
    ui->clock->display(n);
    display->clockDisplay(n);
    if (n == 0)
    {
        timer->stop();
        if (ui->checkBox->checkState())
        {
            display->stop();
        }
        else
        {
            display->revealVideo();
        }
    }
}

void ControlWindow::setVolume(int n)
{
    display->setVolume(n);
}
