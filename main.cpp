#include "App/AppConfigurator.h"
#include "App/AppConfigReader.h"
#include "App/database.h"

#include "QtImplementations/display.h"

#include "AppQt/appconfiguratorqt.h"
#include <QMetaType>
#include <QApplication>
#include <QScopedPointer>

#include <QVector>
#include "Entities/StatisticItem.h"

Q_DECLARE_METATYPE(StatisticItem)
Q_DECLARE_METATYPE(QVector<StatisticItem>)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString cfgName = "config.ini";
    AppConfigReader reader;
    auto cfg = reader.Read(cfgName);

    qRegisterMetaType<StatisticItem>();
    qRegisterMetaType<QVector<StatisticItem>>();

    // db test
//    Database ;

//    db.setSlot(Slot { 2, Item("pen2", 50), 20, true, 10 } );
//    db.unblockItem("pen");
//    db.setItemSlot("piter pen", 3);
//    db.deleteItem("piter pen");
//    db.setItemPrice("piter pen", 100);

//    Slot s = db.getSlot(db.getSlotNumberByItemName("piter pen"));
//    qDebug() << s.item.GetName() << s.item.GetMoneyAmount() << "\n";
//    db.setSlot(Slot { 1, Item("pen", 10), 20, true, 10 } );

//    db.setItem("piter pen", 30, 1);
    //

//    db.setBalance(70);
//    qDebug() << db.getBalance() << " = BALANCE";

//    db.setAllSlots({ Slot { 1, Item("pen", 10), 20 }, Slot { 2, Item("pen2", 15), 20 } });
//    Slot s = db.getSlot(2);
//    qDebug() << "slot 2: " << s.item.GetName();

//    db.setSlot(Slot { 3, Item("name", 1000), 500 });

//    db.setCoinCount(50, 2);
//    db.setCoinCount(50, 3);
//    db.setCoinCount(100, 1);

//    qDebug() << "50 value coins: " << db.getCoinCount(50);

//    db.setBanknoteCount(500, 2);
//    db.setBanknoteCount(500, 3);
//    db.setBanknoteCount(1000, 1);

//    qDebug() << "5 rubles: " << db.getBanknoteCount(500);
    //

    QScopedPointer<AppConfigurator> configurator(new AppConfiguratorQt(cfg));
    configurator->Run();

//    MainWindow w;
//    w.show();
    return a.exec();
}
