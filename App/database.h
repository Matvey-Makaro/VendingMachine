#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QList>
#include <QtSql>
#include <QSqlDatabase>

#include "Types.h"
#include "Entities/Slot.h"

class QSqlQuery;

class Database
{
public:
    Database(const QString& fileName);
    ~Database();

    void setBalance(MoneyAmount balance);
    MoneyAmount getBalance();

    void setAllSlots(const QList<Slot>& slotsData);
    Slot getSlot(int id);
    void setSlot(const Slot& s);

private:
    bool _execShowError(QSqlQuery& q, const QString& queryStr);

    void _createTablesIfNotExist();

    QSqlDatabase _db;
};

#endif // DATABASE_H
