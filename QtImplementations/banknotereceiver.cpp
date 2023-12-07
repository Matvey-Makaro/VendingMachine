#include "banknotereceiver.h"

BanknoteReceiver::BanknoteReceiver(QWidget *parent)
    : _widget(parent)
{
    connect(&_widget, &BanknoteReceiverWidget::BanknoteReceived, [this](const Banknote& b){ emit BanknoteReceived(b); });

    _widget.show();
}
