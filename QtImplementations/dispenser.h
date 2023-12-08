#ifndef DISPENSER_H
#define DISPENSER_H

#include "Interfaces/IDispenser.h"

class Dispenser : public IDispenser
{
    Q_OBJECT

public:
    void GiveItem(int slotIndex) override;
};
using DispenserShp = QSharedPointer<Dispenser>;

#endif // DISPENSER_H
