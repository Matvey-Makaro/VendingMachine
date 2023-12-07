#include "changedispenser.h"

#include <QMessageBox>

void ChangeDispenser::GiveCoin(int valKopecks)
{
    QMessageBox::information(nullptr, "Выдана монета", tr("ВЫДАНА МОНЕТА НОМИНАЛОМ %1 КОПЕЕК").arg(valKopecks),
                             QMessageBox::Ok);
}
