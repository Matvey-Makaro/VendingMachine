#pragma once

#include "Entities/Banknote.h"
#include "IDevice.h"

class IBanknoteReceiver : public IDevice
{
    Q_OBJECT

signals:
    void BanknoteReceived(const Banknote& banknote);
};
using IBanknoteReceiverShp = QSharedPointer<IBanknoteReceiver>;
