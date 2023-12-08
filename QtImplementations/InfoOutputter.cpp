#include <QMessageBox>
#include "InfoOutputter.h"


void InfoOutputter::Output(Messages msg)
{
    QMessageBox::information(nullptr, "Сообщение", ToText(msg), QMessageBox::Ok);
}

QString InfoOutputter::ToText(Messages msg) const
{
    if(msg == Messages::ProductIsTemporarilyUnavailable)
        return "Продукт временно недоступен";
    else if(msg == Messages::EnterItemNumber)
        return "Введите номер товара";
    else if(msg == Messages::CanNotGetChange)
        return "Не получится выдать сдачу.";
    else if(msg == Messages::EnterValidItemNumber)
        return "Введите допустимый номер товара";
    else if(msg == Messages::NotEnoughCash)
        return "Недостаточно средств";
    else if(msg == Messages::MachineIsTemporarilyUnavailable)
        return "Аппарат временно недоступен";
    else if(msg == Messages::GetItem)
        return "Заберите товар";
    else Q_ASSERT(false);
}
