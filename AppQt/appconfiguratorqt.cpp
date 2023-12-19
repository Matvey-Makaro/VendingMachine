#include "appconfiguratorqt.h"

#include "MainWindow.h"

VendingMachineDevicesShp AppConfiguratorQt::CreateDevices()
{
    auto devices = VendingMachineDevicesShp::create();

    BanknoteReceiverShp banknoteReceiver = BanknoteReceiverShp::create(&_mainWindow);
    devices->BanknoteReceiver = banknoteReceiver;

    CardReaderShp cardReader = CardReaderShp::create(&_mainWindow);
    devices->CardReader = cardReader;

    devices->ChangeDispenser = ChangeDispenserShp::create();

    CoinReceiverShp coinReceiver = CoinReceiverShp::create(&_mainWindow);
    devices->CoinReceiver = coinReceiver;

    devices->Dispenser = DispenserShp::create();

    DisplayShp numpadDisplay = DisplayShp::create(&_mainWindow);
    devices->NumpadDisplay = numpadDisplay;
    for(int i = 0; i < _cfg->numOfItemDisplayes; i++)
    {
        devices->ItemDisplays.push_back(DisplayShp::create());
    }
    NumpadShp numpadPtr = NumpadShp::create(&_mainWindow);
    devices->Numpad = numpadPtr;
    devices->InfoOutputter = InfoOutputterShp::create();

    numpadPtr.get()->GetNumpadWidget()->move(_mainWindow.GetUi()->numpad->pos());
    _mainWindow.GetUi()->numpad = numpadPtr.get()->GetNumpadWidget();

    banknoteReceiver.get()->GetWidget()->move(_mainWindow.GetUi()->banknote_receiver->pos());
    _mainWindow.GetUi()->banknote_receiver = banknoteReceiver.get()->GetWidget();

    cardReader.get()->GetWidget()->move(_mainWindow.GetUi()->card_reader->pos());
    _mainWindow.GetUi()->card_reader = cardReader.get()->GetWidget();

    coinReceiver.get()->GetWidget()->move(_mainWindow.GetUi()->coin_receiver->pos());
    _mainWindow.GetUi()->coin_receiver = coinReceiver.get()->GetWidget();

    numpadDisplay.get()->GetWidget()->move(_mainWindow.GetUi()->main_display->pos());
    _mainWindow.GetUi()->main_display = numpadDisplay.get()->GetWidget();

    _mainWindow.show();

    return devices;
}
