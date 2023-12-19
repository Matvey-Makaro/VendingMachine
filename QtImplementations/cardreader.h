#ifndef CARDREADER_H
#define CARDREADER_H

#include "Interfaces/ICardReader.h"

#include "cardreaderwidget.h"

class CardReader : public ICardReader
{
    Q_OBJECT

public:
    CardReader(QWidget* parent = nullptr);

    void SetPrice(MoneyAmount price) override { _price = price; _widget.SetPrice(price); }
    void Cancel() override { _widget.Cancel(); }

    CardReaderWidget* GetWidget() { return &_widget; }

private:
    CardReaderWidget _widget;
    MoneyAmount _price = 0;
};
using CardReaderShp = QSharedPointer<CardReader>;

#endif // CARDREADER_H
