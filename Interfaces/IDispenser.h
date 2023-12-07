#pragma once

#include "IDevice.h"

class IDispenser : public IDevice
{
    Q_OBJECT
public:
    virtual void GiveItem(int slotIndex) = 0;
};
