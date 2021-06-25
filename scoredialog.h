#ifndef SCOREDIALOG_H
#define SCOREDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include "player.h"

namespace Ui {
class scoreDialog;
}

class scoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit scoreDialog(QWidget *parent = nullptr);
    ~scoreDialog();
    void setPlayerList(QStringList);
    void updateLayout();
    std::vector<int> getScore();

private:
    Ui::scoreDialog *ui;
    QStringList playerList;
    int playerCount;
    QLabel** playerLabels;
    QCheckBox** titleCheck;
    QCheckBox** artistCheck;
};

#endif // SCOREDIALOG_H
