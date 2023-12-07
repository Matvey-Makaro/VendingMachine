#include "dispenser.h"

#include <QMessageBox>

void Dispenser::GiveItem(int slotIndex)
{
    QMessageBox::information(_parent, "Выдан товар", tr("ВЫДАН ТОВАР ИЗ СЛОТА ") + slotIndex, QMessageBox::Ok);
}
