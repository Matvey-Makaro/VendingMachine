#pragma once

#include <QObject>
#include <QVector>
#include <QHash>
#include <QString>

#include "VendingMachineDevices.h"

#include "Entities/Banknote.h"
#include "Entities/Coin.h"

#include "Types.h"

class VendingMachine : public QObject
{
    Q_OBJECT
public:
    // TODO: Инициализировать корректно в конструкторе
    explicit VendingMachine(VendingMachineDevicesShp devices, QObject *parent = nullptr);


private slots:
    void OnBanknoteReceived(const Banknote& banknote);
    void OnCoinReceived(const Coin& coin);
    void OnButtonClicked(Buttons button);

private:
    void AddBanknote(const Banknote& banknote);
    void AddCoin(const Coin& coin);
    void OnOkButtonClicked();
    void OnChangeButtonClicked();

    void InitItemDisplays();

    void SetCurrMoneyAmount(MoneyAmount moneyAmount);
    void UpdateNumpadDisplay();

private:
    VendingMachineDevicesShp _devices;

    MoneyAmount _currMoneyAmount;
    QHash<MoneyAmount, BanknoteVec> _banknotes;
    QHash<MoneyAmount, CoinVec> _coins;

    QString _numpadDisplayText;
    // TODO: Добавить items
};
using VendingMachineShp = QSharedPointer<VendingMachine>;
