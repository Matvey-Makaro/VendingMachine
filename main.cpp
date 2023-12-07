#include "MainWindow.h"
#include "QtImplementations/display.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Display display;
    display.getWidget().show();
    display.SetText("hello world");
//    MainWindow w;
//    w.show();
    return a.exec();
}
