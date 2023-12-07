#pragma once

#include "IDevice.h"
#include "Entities/Coin.h"

class ICoinReceiver : public IDevice
{
    Q_OBJECT

signals:
    void CoinReceived(const Coin& coin);
};
