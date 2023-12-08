#include "dispenser.h"

#include <QMessageBox>

void Dispenser::GiveItem(int slotIndex)
{
    QMessageBox::information(nullptr, "Выдан товар", tr("ВЫДАН ТОВАР ИЗ СЛОТА ") + QString::number(slotIndex + 1),
                             QMessageBox::Ok);
}
