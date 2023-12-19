#include "AppConfigurator.h"

AppConfigurator::AppConfigurator(AppConfigShp cfg) :
    _cfg(std::move(cfg))
{}

void AppConfigurator::Run()
{
    _machine = VendingMachineShp::create(CreateDevices());
    _serverGateway = ServerGatewayShp::create();

    _serverGateway->moveToThread(&_serverGatewayThread);

    QObject::connect(_serverGateway.data(), &ServerGateway::BlockItemSignal,
                     _machine.data(), &VendingMachine::OnBlockItem);
    QObject::connect(&_serverGatewayThread, &QThread::started,
                     _serverGateway.data(), &ServerGateway::Run);
    _serverGatewayThread.start();

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
    devices->InfoOutputter = InfoOutputterShp::create();

    return devices;
}
