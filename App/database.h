#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QtSql>
#include <QSqlDatabase>

class Database
{
public:
    Database(const QString& fileName);

private:
    QSqlDatabase _db;
};

#endif // DATABASE_H
