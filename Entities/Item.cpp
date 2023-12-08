#include "Item.h"

Item::Item(QString name, MoneyAmount price) :
    _name(std::move(name)),
    _price(price)
{}

QString Item::GetName() const
{
    return _name;
}

void Item::SetName(const QString& name)
{
    _name = name;
}

MoneyAmount Item::GetMoneyAmount() const
{
    return _price;
}

void Item::SetMoneyAmount(const MoneyAmount& price)
{
    _price = price;
}
