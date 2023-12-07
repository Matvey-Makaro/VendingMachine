#pragma once


#include "IDevice.h"
#include "Types.h"

class ICardReader : public IDevice
{
public:
    virtual void SetPrice(MoneyAmount price) = 0;
    virtual void Cancel() = 0;

signals:
    void Enabled();
    void Paid();
};
