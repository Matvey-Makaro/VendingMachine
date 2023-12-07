#include "App/AppConfigurator.h"
#include "App/AppConfigReader.h"

#include "MainWindow.h"
#include "QtImplementations/display.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString cfgName = "config.ini";
    AppConfigReader reader;
    auto cfg = reader.Read(cfgName);

    AppConfigurator configurator(cfg);
    configurator.Run();

//    MainWindow w;
//    w.show();
    return a.exec();
}
