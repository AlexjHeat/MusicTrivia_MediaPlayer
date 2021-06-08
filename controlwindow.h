#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include "playlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ControlWindow; }
QT_END_NAMESPACE

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

    void on_actionAdd_Folder_triggered();

    void on_actionRemove_triggered();

private:
    Ui::ControlWindow *ui;
    Playlist *active;
};
#endif // CONTROLWINDOW_H
