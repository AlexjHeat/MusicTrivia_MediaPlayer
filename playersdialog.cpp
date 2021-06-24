#include "playersdialog.h"
#include "ui_playersdialog.h"
#include <QMessageBox>

PlayersDialog::PlayersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayersDialog)
{
    ui->setupUi(this);
    ui->playerCount->setRange(2, MAX_PLAYER_SIZE);

    arr = new QLineEdit*[MAX_PLAYER_SIZE];
    for(int i = 0; i <MAX_PLAYER_SIZE; i++)
    {
        arr[i] = new QLineEdit;
        arr[i]->setText("Player " + QString::number(i + 1));
    }

    ui->verticalLayout->insertWidget(0, arr[0]);
    ui->verticalLayout->insertWidget(1, arr[1]);
    playerCount = 2;

    connect(ui->playerCount, SIGNAL(valueChanged(int)), this, SLOT(playerCountUpdate(int)));
}

PlayersDialog::~PlayersDialog()
{
    delete ui;
    delete arr;
}

void PlayersDialog::playerCountUpdate(int playerCountNew)
{
    if (playerCountNew > playerCount)
    {
        for(int i = playerCount; i < playerCountNew; i++)
        {
            ui->verticalLayout->insertWidget(i, arr[i]);
        }
    }
    else
    {
        for(int i = playerCount - 1; i > playerCountNew - 1; i--)
        {

            ui->verticalLayout->removeWidget(arr[i]);
            delete arr[i];
            arr[i] = new QLineEdit;
            arr[i]->setText("Player " + QString::number(i + 1));
        }
    }
    playerCount = playerCountNew;
}

QStringList PlayersDialog::getPlayerList()
{
    QStringList playerList;
    for(int i = 0; i < playerCount; i++)
    {
        playerList.append(arr[i]->text());

    }
    return playerList;
}

int PlayersDialog::getPlayerCount()
{
    return playerCount;
}
