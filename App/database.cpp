#include "database.h"
#include <QDebug>

Database::Database(const QString &fileName)
    : _db(QSqlDatabase::addDatabase("QSQLITE"))
{
    _db.setDatabaseName(fileName);

    if (!_db.open())
    {
        qDebug() << _db.lastError().text();
    }
}
