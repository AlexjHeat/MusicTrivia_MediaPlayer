#include "controlwindow.h"
#include "displaywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlWindow w;
    w.setWindowTitle("Control");
    w.show();
    DisplayWindow d;
    d.setWindowTitle("Display");
    d.show();
    return a.exec();
}
