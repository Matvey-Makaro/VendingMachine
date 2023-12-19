#pragma once

#include <QObject>
#include <QVector>
#include <QHash>
#include <QString>
#include <map>
#include <optional>

#include "App/AppConfig.h"
#include "VendingMachineDevices.h"

#include "App/database.h"

#include "Entities/Banknote.h"
#include "Entities/Coin.h"
#include "Entities/Item.h"

#include "Types.h"

class VendingMachine : public QObject
{
    Q_OBJECT

    using MoneyAmountToCoinCount = std::map<MoneyAmount, int>;
    using MoneyAmountToCoinCountOpt = std::optional<MoneyAmountToCoinCount>;
public:
    // TODO: Инициализировать корректно в конструкторе
    explicit VendingMachine(VendingMachineDevicesShp devices, Database& db, QObject *parent = nullptr);

public slots:
    void OnBlockItem(QString itemName);

private slots:
    void OnBanknoteReceived(const Banknote& banknote);
    void OnCoinReceived(const Coin& coin);
    void OnButtonClicked(Buttons button);
    void OnCardReaderEnabled();
    void OnCardReaderPaid();

private:
    void AddBanknote(const Banknote& banknote);
    void AddCoin(const Coin& coin);
    void OnOkButtonClicked();
    void OnChangeButtonClicked();

    void InitItemDisplays();

    void SetCurrMoneyAmount(MoneyAmount moneyAmount);
    void UpdateNumpadDisplay();

    MoneyAmountToCoinCountOpt CalculateChange(MoneyAmount change);

private:
    Database& _db;

    VendingMachineDevicesShp _devices;

    MoneyAmount _currMoneyAmount;
    std::map<MoneyAmount, BanknoteVec> _banknotes;
    std::map<MoneyAmount, CoinVec> _coins;

    QString _numpadDisplayText;
//    QVector<Item> _items;
    QVector<Slot> _slots;

    bool _isCardReaderEnabled = false;
    int _lastItemIndex = 0;
};
using VendingMachineShp = QSharedPointer<VendingMachine>;
