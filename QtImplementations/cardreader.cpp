#include "cardreader.h"

CardReader::CardReader(QWidget *parent) : _widget(parent)
{
    connect(&_widget, &CardReaderWidget::Enabled, [this](){ emit Enabled(); });
    connect(&_widget, &CardReaderWidget::Paid, [this](){ emit Paid(); });

    _widget.show();
}
