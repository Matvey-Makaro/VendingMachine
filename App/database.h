#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QtSql>
#include <QSqlDatabase>

#include "Types.h"

class QSqlQuery;

class Database
{
public:
    Database(const QString& fileName);
    ~Database();

    void setBalance(MoneyAmount balance);
    MoneyAmount getBalance();

private:
    bool _execShowError(QSqlQuery& q, const QString& queryStr);

    void _createTablesIfNotExist();

    QSqlDatabase _db;
};

#endif // DATABASE_H
