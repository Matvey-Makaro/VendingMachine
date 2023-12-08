#include "AppConfigurator.h"

AppConfigurator::AppConfigurator(AppConfigShp cfg) :
    _cfg(std::move(cfg))
{}

void AppConfigurator::Run()
{
    _machine = VendingMachineShp::create(CreateDevices());
}

VendingMachineDevicesShp AppConfigurator::CreateDevices()
{
    auto devices = VendingMachineDevicesShp::create();

    devices->BanknoteReceiver = BanknoteReceiverShp::create();
    devices->CardReader = CardReaderShp::create();
    devices->ChangeDispenser = ChangeDispenserShp::create();
    devices->CoinReceiver = CoinReceiverShp::create();
    devices->Dispenser = DispenserShp::create();
    devices->NumpadDisplay = DisplayShp::create();
    for(int i = 0; i < _cfg->numOfItemDisplayes; i++)
    {
        devices->ItemDisplays.push_back(DisplayShp::create());
    }
    devices->Numpad = NumpadShp::create();

    return devices;
}