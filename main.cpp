#include "App/AppConfigurator.h"
#include "App/AppConfigReader.h"
#include "App/database.h"

#include "MainWindow.h"
#include "QtImplementations/display.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString cfgName = "config.ini";
    AppConfigReader reader;
    auto cfg = reader.Read(cfgName);

    // db test
    QString dbFile = "app.db";
    Database db(dbFile);
    db.setBalance(70);
    qDebug() << db.getBalance() << " = BALANCE";

    db.setAllSlots({ Slot { 1, Item("pen", 10), 20 }, Slot { 2, Item("pen2", 15), 20 } });
    //

    AppConfigurator configurator(cfg);
    configurator.Run();

//    MainWindow w;
//    w.show();
    return a.exec();
}
