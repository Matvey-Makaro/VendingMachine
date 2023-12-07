#ifndef COINRECEIVER_H
#define COINRECEIVER_H

#include "Interfaces/ICoinReceiver.h"
#include "coinreceiverwidget.h"

class CoinReceiver : public ICoinReceiver
{
    Q_OBJECT

public:
    CoinReceiver(QWidget* parent = nullptr);

private:
    CoinReceiverWidget _coinRecWidget;
};

#endif // COINRECEIVER_H