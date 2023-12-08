#pragma once

#include <QSharedPointer>

#include "Interfaces/IBanknoteReceiver.h"
#include "Interfaces/ICardReader.h"
#include "Interfaces/IChangeDispenser.h"
#include "Interfaces/ICoinReceiver.h"
#include "Interfaces/IDispenser.h"
#include "Interfaces/IDisplay.h"
#include "Interfaces/INumpad.h"
#include "Interfaces/IInfoOutputter.h"

struct VendingMachineDevices
{
    IBanknoteReceiverShp BanknoteReceiver;
    ICardReaderShp CardReader;
    IChangeDispenserShp ChangeDispenser;
    ICoinReceiverShp CoinReceiver;
    IDispenserShp Dispenser;
    IDisplayShp NumpadDisplay;
    QVector<IDisplayShp> ItemDisplays;
    INumpadShp Numpad;
    IInfoOutputterShp InfoOutputter;
};
using VendingMachineDevicesShp = QSharedPointer<VendingMachineDevices>;
