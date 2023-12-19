#ifndef BANKNOTERECEIVER_H
#define BANKNOTERECEIVER_H

#include <QSharedPointer>
#include "Interfaces/IBanknoteReceiver.h"
#include "banknotereceiverwidget.h"

class BanknoteReceiver : public IBanknoteReceiver
{
    Q_OBJECT

public:
    BanknoteReceiver(QWidget* parent = nullptr);

    BanknoteReceiverWidget* GetWidget() { return &_widget; }

private:
    BanknoteReceiverWidget _widget;
};
using BanknoteReceiverShp = QSharedPointer<BanknoteReceiver>;

#endif // BANKNOTERECEIVER_H
