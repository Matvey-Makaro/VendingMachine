#ifndef COINRECEIVER_H
#define COINRECEIVER_H

#include "Interfaces/ICoinReceiver.h"
#include "coinreceiverwidget.h"

class CoinReceiver : public ICoinReceiver
{
    Q_OBJECT

public:
    CoinReceiver(QWidget* parent = nullptr);

    CoinReceiverWidget* GetWidget() { return &_coinRecWidget; }

private:
    CoinReceiverWidget _coinRecWidget;
};
using CoinReceiverShp = QSharedPointer<CoinReceiver>;

#endif // COINRECEIVER_H
