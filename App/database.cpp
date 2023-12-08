#include "database.h"
#include <QDebug>
#include <QSqlQuery>
#include <QString>

Database::Database(const QString &fileName)
    : _db(QSqlDatabase::addDatabase("QSQLITE"))
{
    _db.setDatabaseName(fileName);

    if (!_db.open())
    {
        qDebug() << _db.lastError().text();
    }

    _createTablesIfNotExist();
}

Database::~Database()
{
    if (_db.isOpen())
    {
        _db.close();
    }
}

void Database::setBalance(MoneyAmount balance)
{
    // Записать значение в таблицу balance в нулевую строку
    QSqlQuery q;

    if (!_execShowError(q, QString("insert into balance (id, value_kopecks) values (1, %1)").arg(balance)))
    {
        _execShowError(q, QString("update balance set value_kopecks = %1 where id = 1;").arg(balance));
    }
}

MoneyAmount Database::getBalance()
{
    QSqlQuery q("select value_kopecks from balance where id = 1;");
    q.next();
    return q.value(0).toInt();
}

bool Database::_execShowError(QSqlQuery &q, const QString &queryStr)
{
    bool res = q.exec(queryStr);

    if (!res)
    {
        qDebug() << q.lastError().text();
    }

    return res;
}

void Database::_createTablesIfNotExist()
{
    // Слоты
    // Баланс
    // Монеты
    // Банкноты

    QSqlQuery("create table slots (id int primary key not null, name text, price_kopecks int, count int);");
    QSqlQuery("create table balance (id int primary key not null, value_kopecks int);");
    QSqlQuery("create table coins ("
              "value int primary key not null, "
              "count int "
              ");");
    QSqlQuery("create table banknotes ("
              "value int primary key not null, "
              "count int "
              ");");
}
