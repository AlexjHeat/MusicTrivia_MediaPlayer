#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ControlWindow; }
QT_END_NAMESPACE

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    ControlWindow(QWidget *parent = nullptr);
    ~ControlWindow();

private:
    Ui::ControlWindow *ui;
};
#endif // CONTROLWINDOW_H
