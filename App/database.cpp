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

void Database::setAllSlots(const QList<Slot> &slotsData)
{
    QSqlQuery q;
    _execShowError(q, "delete from slots;");

    for (const auto& s : slotsData)
    {
        _execShowError(q, QString("insert into slots (id, name, price_kopecks, count)"
                                  "values (%1, '%2', %3, %4);")
                       .arg(s.id).arg(s.item.GetName()).arg(s.item.GetMoneyAmount()).arg(s.count));
    }
}

Slot Database::getSlot(int id)
{
    QSqlQuery q(QString("select name, price_kopecks, count from slots where id = %1;").arg(id));
    q.next();
    QString name = q.value(0).toString();
    MoneyAmount priceKopecks = q.value(1).toInt();
    int count = q.value(2).toInt();

    return Slot { id, Item(name, priceKopecks), count };
}

void Database::setSlot(const Slot &s)
{
    QSqlQuery q;

    if (_execShowError(q, QString("update slots set name = '%1', price_kopecks = %2, count = %3 where id = %4")
                       .arg(s.item.GetName()).arg(s.item.GetMoneyAmount()).arg(s.count).arg(s.id)))
    {
        _execShowError(q, QString("insert into slots (id, name, price_kopecks, count)"
                                  "values (%1, '%2', %3, %4);")
                               .arg(s.id).arg(s.item.GetName()).arg(s.item.GetMoneyAmount()).arg(s.count));
    }
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
    // Слоты: задать итемы в каждый слот (массивом), прочитать информацию об итеме по номеру слота,
    // поставить новую инфу об итеме по номеру слота
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
