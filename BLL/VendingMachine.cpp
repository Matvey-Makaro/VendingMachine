#include <QDebug>
#include "VendingMachine.h"

namespace
{
    char ToChar(Buttons button)
    {
        if(button == Buttons::Num0)
            return '0';
        else if(button == Buttons::Num1)
            return '1';
        else if(button == Buttons::Num2)
            return '2';
        else if(button == Buttons::Num3)
            return '3';
        else if(button == Buttons::Num4)
            return '4';
        else if(button == Buttons::Num5)
            return '5';
        else if(button == Buttons::Num6)
            return '6';
        else if(button == Buttons::Num7)
            return '7';
        else if(button == Buttons::Num8)
            return '8';
        else if(button == Buttons::Num9)
            return '9';
        else if(button == Buttons::Del)
            return 'd';
        else if(button == Buttons::Change)
            return 'c';
        else if(button == Buttons::OK)
            return 'k';
        else Q_ASSERT(false);
    }
}

VendingMachine::VendingMachine(VendingMachineDevicesShp devices, QObject *parent) :
    QObject(parent),
    _devices(std::move(devices)),
    _currMoneyAmount(0)
{
    connect(_devices->BanknoteReceiver.data(), &IBanknoteReceiver::BanknoteReceived,
            this, &VendingMachine::OnBanknoteReceived);
    connect(_devices->CoinReceiver.data(), &ICoinReceiver::CoinReceived,
            this, &VendingMachine::OnCoinReceived);
    connect(_devices->Numpad.data(), &INumpad::ButtonClicked,
            this, &VendingMachine::OnButtonClicked);

    InitItemDisplays();
    UpdateNumpadDisplay();
}

void VendingMachine::OnBanknoteReceived(const Banknote& banknote)
{
    qDebug() << "VendingMachine::OnBanknoteReceived()";
    AddBanknote(banknote);
    SetCurrMoneyAmount(_currMoneyAmount + banknote.GetValKopecks());
}

void VendingMachine::OnCoinReceived(const Coin& coin)
{
    AddCoin(coin);
    SetCurrMoneyAmount(_currMoneyAmount + coin.GetValKopecks());
}

void VendingMachine::OnButtonClicked(Buttons button)
{
    if(button == Buttons::OK)
    {
        // TODO: on OK clicked
    }
    else if(button == Buttons::Change)
    {
        // TODO: On Change clicked
    }
    else if(button == Buttons::Del)
    {
        qDebug() << "Del";
        if(_numpadDisplayText.size() != 0)
            _numpadDisplayText.remove(_numpadDisplayText.size() - 1, 1);
    }
    else
    {
        _numpadDisplayText += ToChar(button);
    }
    UpdateNumpadDisplay();
}

void VendingMachine::AddBanknote(const Banknote& banknote)
{
    _banknotes[banknote.GetValKopecks()].push_back(banknote);
}

void VendingMachine::AddCoin(const Coin& coin)
{
    _coins[coin.GetValKopecks()].push_back(coin);
}

void VendingMachine::OnOkButtonClicked()
{
    if(_numpadDisplayText.isEmpty())
    {
        // TODO: Сообщить о том, что надо что-то ввести
    }
    // TODO: Проверить входит ли в допустимый диапазон
    // TODO: Доступен ли товар?
    // TODO: Достаточно ли средств?
    // TODO: Можем ли выдать сдачу?
    // TODO: Отдать товар
}

void VendingMachine::OnChangeButtonClicked()
{
    // Не пустой ли баланс
    // Рассчитать как выдать сдачу
    // Выдать сдачу
}

void VendingMachine::InitItemDisplays()
{
    auto& itemDisplays = _devices->ItemDisplays;
    for(int i = 0; i < itemDisplays.size(); i++)
    {
        QString text = "Item" + QString::number(i + 1) + "\n";
        text += QString::number((i + 1) * 10) + "коп.";
        itemDisplays[i]->SetText(text);
    }
}

void VendingMachine::SetCurrMoneyAmount(MoneyAmount moneyAmount)
{
    _currMoneyAmount = moneyAmount;
    UpdateNumpadDisplay();
}

void VendingMachine::UpdateNumpadDisplay()
{
    // TODO: Формировать нормальную запись для денег: 1р 70коп
    QString text = QString::number(_currMoneyAmount) + "коп.\n";
    text += _numpadDisplayText;
    _devices->NumpadDisplay->SetText(text);
}



