#ifndef BANKNOTERECEIVER_H
#define BANKNOTERECEIVER_H

#include "Interfaces/IBanknoteReceiver.h"
#include "banknotereceiverwidget.h"

class BanknoteReceiver : public IBanknoteReceiver
{
public:
    BanknoteReceiver(QWidget* parent = nullptr);

private:
    BanknoteReceiverWidget _widget;
};

#endif // BANKNOTERECEIVER_H
