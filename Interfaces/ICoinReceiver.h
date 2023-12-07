#pragma once

#include "IDevice.h"

class ICoinReceiver : public IDevice
{
    Q_OBJECT
public:

signals:
    void CoinReceived()
};
