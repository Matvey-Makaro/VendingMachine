#pragma once

#include "BLL/VendingMachineDevices.h"
#include "BLL/VendingMachine.h"

#include "QtImplementations/display.h"
#include "QtImplementations/numpad.h"
#include "QtImplementations/dispenser.h"
#include "QtImplementations/coinreceiver.h"
#include "QtImplementations/banknotereceiver.h"
#include "QtImplementations/changedispenser.h"
#include "QtImplementations/cardreader.h"

#include "AppConfig.h"

class AppConfigurator
{
public:
    AppConfigurator(AppConfigShp cfg);
    void Run();

private:
    VendingMachineDevicesShp CreateDevices();

private:
    AppConfigShp _cfg;
    VendingMachineShp _machine;
};

