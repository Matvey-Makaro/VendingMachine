#pragma once

#include <QString>
#include "Types.h"

class Item
{
public:
    Item(QString name = "", MoneyAmount price = 0);

    QString GetName() const;
    void SetName(const QString& name);

    MoneyAmount GetMoneyAmount() const;
    void SetMoneyAmount(const MoneyAmount& price);

    bool IsAvailable() const;
    void SetIsAvailable(bool isAvailable);

private:
    QString _name;
    MoneyAmount _price;
    bool _isAvailable;
};

