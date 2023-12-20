#include <QDebug>
#include <QVector>
#include <vector>
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

VendingMachine::VendingMachine(VendingMachineDevicesShp devices, Database& db, QObject *parent) :
    QObject(parent),
    _devices(std::move(devices)),
    _currMoneyAmount(0),
    _db(db)
{
    connect(_devices->BanknoteReceiver.data(), &IBanknoteReceiver::BanknoteReceived,
            this, &VendingMachine::OnBanknoteReceived);
    connect(_devices->CoinReceiver.data(), &ICoinReceiver::CoinReceived,
            this, &VendingMachine::OnCoinReceived);
    connect(_devices->Numpad.data(), &INumpad::ButtonClicked,
            this, &VendingMachine::OnButtonClicked);
    connect(_devices->CardReader.data(), &ICardReader::Enabled,
            this, &VendingMachine::OnCardReaderEnabled);
    connect(_devices->CardReader.data(), &ICardReader::Paid,
            this, &VendingMachine::OnCardReaderPaid);

    std::vector<int> coinNoms = { 1, 2, 5, 10, 20, 50, 100, 200 };
    std::vector<int> banknoteNoms = { 500, 1000, 2000 };
    for (int nom : coinNoms)
    {
        int numCoinsCurrNom = _db.getCoinCount(nom);
        _coins[nom].insert(_coins[nom].end(), numCoinsCurrNom, Coin(nom));
    }
    for (int nom : banknoteNoms)
    {
        int numBanknotesCurrNom = _db.getBanknoteCount(nom);
        _banknotes[nom].insert(_banknotes[nom].end(), numBanknotesCurrNom, Banknote(nom));
    }
    // прочитать баланс
    SetCurrMoneyAmount(_db.getBalance());

    // прочитать слоты
    _slots = _db.getAllSlots();

    UpdateItemDisplays();
    UpdateNumpadDisplay();
}

void VendingMachine::OnSetItem(QString item, int price, int slot)
{
    qDebug() << "VendingMachine::OnSetItem" << "Item: " << item << "Price: " << price << "Slot" << slot;
    _db.setItem(item, price, slot);
    _slots = _db.getAllSlots();
    UpdateItemDisplays();
}

void VendingMachine::OnSetItemPrice(QString item, int price)
{
    _db.setItemPrice(item, price);
    _slots = _db.getAllSlots();
    UpdateItemDisplays();
}

void VendingMachine::OnSetItemSlot(QString item, int slot)
{
    _db.setItemSlot(item, slot);
    _slots = _db.getAllSlots();

    qDebug() << _slots.size() << "\n";

    UpdateItemDisplays();
}

void VendingMachine::OnDeleteItem(QString item)
{
    qDebug() << "onDeleteItem()\n";
    _db.deleteItem(item);
    _slots = _db.getAllSlots();
    UpdateItemDisplays();
}

void VendingMachine::OnBlockItem(QString item)
{
    _db.blockItem(item);
    _slots = _db.getAllSlots();
}

void VendingMachine::OnUnblockItem(QString item)
{
    _db.unblockItem(item);
    _slots = _db.getAllSlots();
}

void VendingMachine::OnGetCurrBalance()
{
    emit SendBalance(_currMoneyAmount);
}

void VendingMachine::OnSetBalance(int balance)
{
    _db.setBalance(balance);
    SetCurrMoneyAmount(balance);
}

void VendingMachine::OnGetStatistic()
{
    emit SendStatistic(QVector<StatisticItem>::fromStdVector(_db.getStatistic()));
}

void VendingMachine::OnGetError()
{
    // TODO: Impl...
}

void VendingMachine::OnBanknoteReceived(const Banknote& banknote)
{
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
    if (button == Buttons::OK)
    {
        OnOkButtonClicked();
    }
    else if(button == Buttons::Change)
    {
        OnChangeButtonClicked();
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

void VendingMachine::OnCardReaderEnabled()
{
    _isCardReaderEnabled = true;
    _devices->InfoOutputter->Output(Messages::EnterItemNumber);
}

void VendingMachine::OnCardReaderPaid()
{
    _isCardReaderEnabled = false;
    _devices->Dispenser->GiveItem(_lastItemIndex);

    _devices->InfoOutputter->Output(Messages::GetItem);
}

void VendingMachine::AddBanknote(const Banknote& banknote)
{
    _banknotes[banknote.GetValKopecks()].push_back(banknote);
    int prevCount = _db.getBanknoteCount(banknote.GetValKopecks());
    _db.setBanknoteCount(banknote.GetValKopecks(), prevCount + 1);
}

void VendingMachine::AddCoin(const Coin& coin)
{
    _coins[coin.GetValKopecks()].push_back(coin);
    int prevCount = _db.getCoinCount(coin.GetValKopecks());
    _db.setCoinCount(coin.GetValKopecks(), prevCount + 1);
}

bool VendingMachine::isValidIndex(int index)
{
    for (const Slot& slot : _slots)
    {
        if (slot.id == index)
        {
            return true;
        }
    }

    return false;
}

Slot VendingMachine::getSlotByIndex(int index)
{
    for (const Slot& slot : _slots)
    {
        if (slot.id == index)
        {
            return slot;
        }
    }

    return Slot{ -1 };
}

void VendingMachine::OnOkButtonClicked()
{
    if(_numpadDisplayText.isEmpty())
    {
        _devices->InfoOutputter->Output(Messages::EnterItemNumber);
        return;
    }

    int itemIndex = _numpadDisplayText.toInt();
    Slot slot = getSlotByIndex(itemIndex);
    if (slot.id == -1)
    {
        _devices->InfoOutputter->Output(Messages::EnterValidItemNumber);
        return;
    }

//    if(itemIndex < 1 || itemIndex >= _slots.size())
//    {
//        _devices->InfoOutputter->Output(Messages::EnterValidItemNumber);
//        return;
//    }

//    auto& slot = _slots[itemIndex];
    if (slot.blocked)
    {
        _devices->InfoOutputter->Output(Messages::ProductIsTemporarilyUnavailable);
        return;
    }

    _lastItemIndex = itemIndex;
    if(_isCardReaderEnabled)
    {
        _devices->CardReader->SetPrice(slot.item.GetMoneyAmount());
        return;
    }

    if (slot.item.GetMoneyAmount() > _currMoneyAmount)
    {
        _devices->InfoOutputter->Output(Messages::NotEnoughCash);
        return;
    }

    auto change = CalculateChange(_currMoneyAmount - slot.item.GetMoneyAmount());
    if(!change)
    {
        _devices->InfoOutputter->Output(Messages::CanNotGetChange);
        return;
    }

    slot.count--;
    if (slot.count < 0)
    {
        slot.count = 0;
        _devices->InfoOutputter->Output(Messages::ProductIsTemporarilyUnavailable);
        return;
    }
    slot.sold++;

    // продать
    SetCurrMoneyAmount(_currMoneyAmount - slot.item.GetMoneyAmount());
    _db.setSlot(slot);
    _devices->Dispenser->GiveItem(itemIndex);
    _devices->InfoOutputter->Output(Messages::GetItem);
}

void VendingMachine::OnChangeButtonClicked()
{
    auto change = CalculateChange(_currMoneyAmount);
    if (!change)
    {
        _devices->InfoOutputter->Output(Messages::CanNotGetChange);
        return;
    }
    for(const auto& [amount, coinCount] : *change)
    {
        for(int i = 0; i < coinCount; i++)
        {
            _devices->ChangeDispenser->GiveCoin(amount);

            int prevCoinCount = _db.getCoinCount(amount);
            _db.setCoinCount(amount, prevCoinCount - 1);

            _coins[amount].pop_back();
        }
    }
    SetCurrMoneyAmount(0);
}

void VendingMachine::UpdateItemDisplays()
{
    auto& itemDisplays = _devices->ItemDisplays;

    for (auto display : _devices->ItemDisplays)
    {
        display->SetText("");
    }

    for(int i = 0; i < _slots.size(); i++)
    {
        Item item = _slots[i].item;
//        Item item("Item" + QString::number(i + 1), (i + 1) * 10);
//        _items.push_back(item);

        QString text = item.GetName() + "\n";
        text += QString::number(item.GetMoneyAmount()) + "коп.";
        itemDisplays[_slots[i].id - 1]->SetText(text);
    }
}

void VendingMachine::SetCurrMoneyAmount(MoneyAmount moneyAmount)
{
    _currMoneyAmount = moneyAmount;
    _db.setBalance(moneyAmount);
    UpdateNumpadDisplay();
}

void VendingMachine::UpdateNumpadDisplay()
{
    int rubles = _currMoneyAmount / 100;
    int kopecks = _currMoneyAmount % 100;

    QString text = QString("%1р., %2 коп.").arg(rubles).arg(kopecks) + '\n';
    text += _numpadDisplayText;
    _devices->NumpadDisplay->SetText(text);
}

VendingMachine::MoneyAmountToCoinCountOpt VendingMachine::CalculateChange(MoneyAmount change)
{
    MoneyAmountToCoinCount result;
    for(auto it = _coins.crbegin(); it != _coins.crend(); it++)
    {
        auto amount = it->first;
        const auto& coins = it->second;

        int numOfCoins = coins.size();
        int numOfCoinsNeeded = change / amount;
        int numOfCoinsToGive = numOfCoins > numOfCoinsNeeded ? numOfCoinsNeeded : numOfCoins;
        result[amount] = numOfCoinsToGive;
        change -= numOfCoinsToGive * amount;
    }

    if(change != 0)
        return std::nullopt;
    return result;
}
