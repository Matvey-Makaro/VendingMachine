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
        setSlot(s);
    }
}

QVector<Slot> Database::getAllSlots()
{
    QSqlQuery q("select id, name, price_kopecks, count, blocked, sold from slots;");

    QVector<Slot> allSlots;

    while (q.next())
    {
        int id = q.value(0).toInt();
        QString name = q.value(1).toString();
        MoneyAmount priceKopecks = q.value(2).toInt();
        int count = q.value(3).toInt();
        bool blocked = q.value(4).toBool();
        int sold = q.value(5).toInt();

        allSlots.push_back(Slot { id, Item(name, priceKopecks), count, blocked, sold });
    }

    return allSlots;
}

Slot Database::getSlot(int id)
{
    QSqlQuery q(QString("select name, price_kopecks, count, blocked, sold from slots where id = %1;").arg(id));
    q.next();
    QString name = q.value(0).toString();
    MoneyAmount priceKopecks = q.value(1).toInt();
    int count = q.value(2).toInt();
    bool blocked = q.value(3).toBool();
    int sold = q.value(4).toInt();

    qDebug() << id << "\n";

    return Slot { id, Item(name, priceKopecks), count, blocked, sold };
}

void Database::setSlot(const Slot &s)
{
    QSqlQuery q;

    if (_execShowError(q, QString("update slots set name = '%1', price_kopecks = %2, count = %3, "
                                  "blocked = %4, sold = %5, id = %6 where id = %7")
                       .arg(s.item.GetName()).arg(s.item.GetMoneyAmount()).arg(s.count)
                       .arg(s.blocked).arg(s.sold).arg(s.id).arg(s.id)))
    {
        _execShowError(q, QString("insert into slots (id, name, price_kopecks, count, blocked, sold)"
                                  "values (%1, '%2', %3, %4, %5, %6);")
                               .arg(s.id).arg(s.item.GetName()).arg(s.item.GetMoneyAmount()).arg(s.count).arg(s.blocked).arg(s.sold));
    }
}

void Database::setItem(QString name, int priceKopecks, int slotNum)
{
    Slot prev = getSlot(slotNum);  // предыдущие данные

    Slot s;
    s.id = slotNum;
    s.item = Item(name, priceKopecks);
    s.blocked = prev.blocked;
    //s.count = prev.count;
    //xxx
    s.count = 10;
    s.sold = prev.sold;

    setSlot(s);
}

void Database::setItemPrice(QString name, int newPriceKopecks)
{
    Slot s = getSlot(getSlotNumberByItemName(name));
    s.item.SetMoneyAmount(newPriceKopecks);
    setSlot(s);
}

int Database::getSlotNumberByItemName(QString name)
{
    QSqlQuery q(QString("select id from slots where name = '%1';").arg(name));
    q.next();
    return q.value(0).toInt();
}

void Database::setItemSlot(QString name, int slot)
{
    QSqlQuery q;

    int prevId = getSlotNumberByItemName(name);
    _execShowError(q, QString("update slots set id = %1 where name = '%2'")
                           .arg(slot).arg(name));
}

void Database::deleteItem(QString name)
{
    QSqlQuery q;
    _execShowError(q, QString("delete from slots where name = '%1'")
                   .arg(name));
}

void Database::blockItem(QString name)
{
    QSqlQuery q;
    _execShowError(q, QString("update slots set blocked = true where name = '%1'").arg(name));
}

void Database::unblockItem(QString name)
{
    QSqlQuery q;
    _execShowError(q, QString("update slots set blocked = false where name = '%1'").arg(name));
}

void Database::setCoinCount(int value, int count)
{
    QSqlQuery q;

    if (_execShowError(q, QString("update coins set count = %1 where value = %2")
                       .arg(count).arg(value)))
    {
        _execShowError(q, QString("insert into coins (value, count)"
                                  "values (%1, %2);")
                               .arg(value).arg(count));
    }
}

int Database::getCoinCount(int value)
{
    QSqlQuery q(QString("select count from coins where value = %1;").arg(value));
    q.next();

    return q.value(0).toInt();
}

void Database::setBanknoteCount(int value, int count)
{
    QSqlQuery q;

    if (_execShowError(q, QString("update banknotes set count = %1 where value = %2")
                       .arg(count).arg(value)))
    {
        _execShowError(q, QString("insert into banknotes (value, count)"
                                  "values (%1, %2);")
                               .arg(value).arg(count));
    }
}

int Database::getBanknoteCount(int value)
{
    QSqlQuery q(QString("select count from banknotes where value = %1;").arg(value));
    q.next();

    return q.value(0).toInt();
}

std::vector<StatisticItem> Database::getStatistic()
{
    std::vector<StatisticItem> items;

    QSqlQuery q("select name, sold from slots;");

    while (q.next())
    {
        StatisticItem newItem;
        newItem.item = q.value(0).toString();
        newItem.numOfSales = q.value(1).toInt();
        items.push_back(newItem);
    }

    return items;
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
    // Монеты: задать количество монет определённого номинала, получить количество монет опр. номинала,
    // получить все монеты
    // Банкноты: то же самое

    QSqlQuery("create table slots (id int primary key not null, name text, "
              "price_kopecks int, count int, blocked boolean, sold int);");

    QSqlQuery("create table balance (id int primary key not null, value_kopecks int);");
    QSqlQuery("insert into balance (id, value_kopecks) values (1, 0);");

    QSqlQuery("create table coins ("
              "value int primary key not null, "
              "count int "
              ");");
    QSqlQuery("insert into coins (value, count) values (1, 0);");
    QSqlQuery("insert into coins (value, count) values (2, 0);");
    QSqlQuery("insert into coins (value, count) values (5, 0);");
    QSqlQuery("insert into coins (value, count) values (10, 0);");
    QSqlQuery("insert into coins (value, count) values (20, 0);");
    QSqlQuery("insert into coins (value, count) values (50, 0);");
    QSqlQuery("insert into coins (value, count) values (100, 0);");
    QSqlQuery("insert into coins (value, count) values (200, 0);");

    QSqlQuery("create table banknotes ("
              "value int primary key not null, "
              "count int "
              ");");
    QSqlQuery("insert into banknotes (value, count) values (500, 0);");
    QSqlQuery("insert into banknotes (value, count) values (1000, 0);");
    QSqlQuery("insert into banknotes (value, count) values (2000, 0);");
}
