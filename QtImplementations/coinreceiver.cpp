#include "coinreceiver.h"

CoinReceiver::CoinReceiver(QWidget *parent)
    : _coinRecWidget(parent)
{
    connect(&_coinRecWidget, &CoinReceiverWidget::CoinReceived, [this](const Coin& coin){ emit CoinReceived(coin); });

    _coinRecWidget.show();
}
