#ifndef PLAYERSDIALOG_H
#define PLAYERSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>


namespace Ui {
class PlayersDialog;
}

const int MAX_PLAYER_SIZE = 12;
class PlayersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayersDialog(QWidget *parent = nullptr);
    ~PlayersDialog();
    QStringList getPlayerList();
    int getPlayerCount();

private slots:
    void playerCountUpdate(int);

private:
    Ui::PlayersDialog *ui;
    int playerCount;
    QLineEdit** arr;
    QVBoxLayout* layout;

};

#endif // PLAYERSDIALOG_H
