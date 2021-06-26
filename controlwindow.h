#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QString>
#include <QInputDialog>
#include <QMessageBox>
#include <QTimer>

#include "playlist.h"
#include "displaywindow.h"
#include "playersdialog.h"
#include "player.h"
#include "scoredialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ControlWindow; }
QT_END_NAMESPACE

enum songState{playing, paused, stopped};

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    ControlWindow(QWidget *parent = nullptr);
    ~ControlWindow();

private slots:
    void on_actionLoad_triggered();
    void on_actionSave_triggered();
    void on_actionCreate_triggered();
    void on_actionAdd_triggered();
    void on_actionRemove_triggered();
    void on_actionSort_triggered();
    void on_actionRename_triggered();

    void displaySongData(QModelIndex);
    void updateArtist(QString);
    void updateTitle(QString);
    void updateStartTime(QString);
    void updateGuessTime(QString);

    void buttonPlay();
    void countdown();

    void on_actionNew_Game_triggered();

    void on_buttonScore_released();
    void on_buttonStop_released();

public slots:
    void newGameUpdate();
    void scoreUpdate();

private:
    Ui::ControlWindow *ui;
    DisplayWindow* display;
    Playlist *active;
    QStringListModel* listModel;
    int i;
    Song current;

    QTimer* timer;
    int guessTime;


    songState state;

    PlayersDialog* newGameMenu;
    Player playerList[MAX_PLAYER_SIZE];
    int playerCount;

    scoreDialog* scoreMenu;
};
#endif // CONTROLWINDOW_H
