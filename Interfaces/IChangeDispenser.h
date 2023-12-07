#pragma once

#include "IDevice.h"

class IChangeDispenser : public IDevice
{
public:
    virtual void GiveCoin(int valKopecks) = 0;
};
