#ifndef STATISTICITEM_H
#define STATISTICITEM_H

#include <QString>

struct StatisticItem
{
    StatisticItem() = default;
    ~StatisticItem() = default;

    QString item;
    int numOfSales;
};

#endif // STATISTICITEM_H
