#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "playlist.h"

using namespace std;



ControlWindow::ControlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ControlWindow)
    , active(NULL)
{
    ui->setupUi(this);

    listModel = new QStringListModel(this);
    ui->playlistView->setDragDropMode(QAbstractItemView::DragDrop);
    ui->playlistView->setEditTriggers(QAbstractItemView::CurrentChanged);
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
}


void ControlWindow::on_actionAdd_triggered()
{
    if(active == NULL)
    {
        QMessageBox::warning(this, "Error", "No active playlist");
        return;
    }
    QString fileName = QFileDialog::getOpenFileName(this, "Select a file", "C:\\Users\\Owner\\Music");
    if(!fileName.isEmpty())
    {
        active->add(fileName);
        //Need to update the listmodel
    }
}


void ControlWindow::on_actionAdd_Folder_triggered()
{

}


void ControlWindow::on_actionRemove_triggered()
{

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
