#pragma once

#include <QString>
#include "Types.h"

class Item
{
public:
    Item(QString name, MoneyAmount price);

    QString GetName() const;
    void SetName(const QString& name);

    MoneyAmount GetMoneyAmount() const;
    void SetMoneyAmount(const MoneyAmount& price);

private:
    QString _name;
    MoneyAmount _price;
};

