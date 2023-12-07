#ifndef DISPENSER_H
#define DISPENSER_H

#include "Interfaces/IDispenser.h"

class Dispenser : public IDispenser
{
    Q_OBJECT

public:
    void GiveItem(int slotIndex) override;
};

#endif // DISPENSER_H
