#include "controlwindow.h"
#include "displaywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlWindow c;
    c.setWindowTitle("Control");
    c.show();
    return a.exec();
}
