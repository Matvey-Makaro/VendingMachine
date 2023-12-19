#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QList>
#include <QtSql>
#include <QSqlDatabase>

#include "Types.h"
#include "Entities/Slot.h"
#include "Entities/StatisticItem.h"

class QSqlQuery;

class Database
{
public:
    Database(const QString& fileName);
    ~Database();

    void setBalance(MoneyAmount balance);
    MoneyAmount getBalance();

    void setAllSlots(const QList<Slot>& slotsData);
    QVector<Slot> getAllSlots();

    Slot getSlot(int id);
    void setSlot(const Slot& s);
    void setItem(QString name, int priceKopecks, int slotNum);
    void setItemPrice(QString name, int newPriceKopecks);
    int getSlotNumberByItemName(QString name);
    void setItemSlot(QString name, int slot);
    void deleteItem(QString name);
    void blockItem(QString name);
    void unblockItem(QString name);

    void setCoinCount(int value, int count);
    int getCoinCount(int value);

    void setBanknoteCount(int value, int count);
    int getBanknoteCount(int value);

    std::vector<StatisticItem> getStatistic();


private:

    bool _execShowError(QSqlQuery& q, const QString& queryStr);

    void _createTablesIfNotExist();

    QSqlDatabase _db;
};

#endif // DATABASE_H
