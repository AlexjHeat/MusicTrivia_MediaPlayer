#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "playlist.h"

#include <QString>
#include <QInputDialog>
#include <iostream>
using namespace std;



ControlWindow::ControlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ControlWindow)
    , active(NULL)
{
    ui->setupUi(this);
}

ControlWindow::~ControlWindow()
{
    delete ui;
}


void ControlWindow::on_actionLoad_triggered()
{

}


void ControlWindow::on_actionSave_triggered()
{

}


void ControlWindow::on_actionCreate_triggered()
{
    bool ok;
    QString nameInput = QInputDialog::getText(this, "Create new playlist", "Enter a name for the new playlist", QLineEdit::Normal, "playlist_name", &ok);
    if (!ok) { return; }

    if (active->isUpdated())
    {

    }

    active = new Playlist(nameInput);

}


void ControlWindow::on_actionAdd_triggered()
{

}


void ControlWindow::on_actionAdd_Folder_triggered()
{

}


void ControlWindow::on_actionRemove_triggered()
{

}
