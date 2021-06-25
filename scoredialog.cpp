#include "scoredialog.h"
#include "ui_scoredialog.h"

scoreDialog::scoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scoreDialog)
{
    ui->setupUi(this);
    playerLabels = new QLabel*;
    titleCheck = new QCheckBox*;
    artistCheck = new QCheckBox*;
}

scoreDialog::~scoreDialog()
{
    delete ui;
    delete playerLabels;
    delete titleCheck;
    delete artistCheck;
}

void scoreDialog::setPlayerList(QStringList playerList)
{
    this->playerList = playerList;
    playerCount = playerList.length();
}

void scoreDialog::updateLayout()
{
    delete playerLabels;
    delete titleCheck;
    delete artistCheck;

    playerLabels = new QLabel*[playerCount];
    titleCheck = new QCheckBox*[playerCount];
    artistCheck = new QCheckBox*[playerCount];

    for(int i=0; i < playerCount; i++)
    {
        playerLabels[i] = new QLabel;
        titleCheck[i] = new QCheckBox;
        artistCheck[i] = new QCheckBox;

        playerLabels[i]->setText(playerList[i]);

        ui->playerLayout->addWidget(playerLabels[i]);
        ui->titleLayout->addWidget(titleCheck[i]);
        ui->artistLayout->addWidget(artistCheck[i]);
    }
}

std::vector<int> scoreDialog::getScore()
{
    std::vector<int> scores(playerCount);
    for(int i=0; i < playerCount; i++)
    {
        if(titleCheck[i]->isChecked())
            scores[i]++;
        if(artistCheck[i]->isChecked())
            scores[i]++;
    }
    return scores;
}
