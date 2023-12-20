#include "AppConfigurator.h"

AppConfigurator::AppConfigurator(AppConfigShp cfg) :
    _cfg(std::move(cfg)), _db("app.db")
{}

void AppConfigurator::Run()
{
    _machine = VendingMachineShp::create(CreateDevices(), _db);
    _serverGateway = ServerGatewayShp::create();

    _serverGateway->moveToThread(&_serverGatewayThread);

    MakeConnections();

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

void AppConfigurator::MakeConnections()
{
    QObject::connect(_serverGateway.data(), &ServerGateway::SetItemSignal,
                     _machine.data(), &VendingMachine::OnSetItem);
    QObject::connect(_serverGateway.data(), &ServerGateway::SetItemPriceSignal,
                     _machine.data(), &VendingMachine::OnSetItemPrice);
    QObject::connect(_serverGateway.data(), &ServerGateway::SetItemSlotSignal,
                     _machine.data(), &VendingMachine::OnSetItemSlot);
    QObject::connect(_serverGateway.data(), &ServerGateway::DeleteItemSignal,
                     _machine.data(), &VendingMachine::OnDeleteItem);
    QObject::connect(_serverGateway.data(), &ServerGateway::BlockItemSignal,
                     _machine.data(), &VendingMachine::OnBlockItem);
    QObject::connect(_serverGateway.data(), &ServerGateway::UnblockItemSignal,
                     _machine.data(), &VendingMachine::OnUnblockItem);
    QObject::connect(_serverGateway.data(), &ServerGateway::GetCurrBalanceSignal,
                     _machine.data(), &VendingMachine::OnGetCurrBalance);
    QObject::connect(_serverGateway.data(), &ServerGateway::SetBalanceSignal,
                     _machine.data(), &VendingMachine::OnSetBalance);
    QObject::connect(_serverGateway.data(), &ServerGateway::GetStatisticSignal,
                     _machine.data(), &VendingMachine::OnGetStatistic);
    QObject::connect(_serverGateway.data(), &ServerGateway::GetErrorSignal,
                     _machine.data(), &VendingMachine::OnGetError);


    QObject::connect(_machine.data(), &VendingMachine::SendBalance,
                     _serverGateway.data(), &ServerGateway::SendBalance);
    QObject::connect(_machine.data(), &VendingMachine::SendStatistic,
                     _serverGateway.data(), &ServerGateway::SendStatistic);
}
