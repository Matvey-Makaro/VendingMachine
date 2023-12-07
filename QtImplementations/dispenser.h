#ifndef DISPENSER_H
#define DISPENSER_H

#include "Interfaces/IDispenser.h"

class Dispenser : public IDispenser
{
    Q_OBJECT

public:
    Dispenser(QWidget* parent = nullptr) : _parent(parent) {}

    void GiveItem(int slotIndex) override;

private:
    QWidget* _parent;
};

#endif // DISPENSER_H
