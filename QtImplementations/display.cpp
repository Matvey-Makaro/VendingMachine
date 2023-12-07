#include "display.h"

Display::Display(QWidget *parent)
    : _widget(parent)
{
    _widget.setWindowTitle("Display");
    _widget.setFixedSize(300, 100);

    _dataLineEdit = new QLineEdit(&_widget);
    _dataLineEdit->resize(_widget.size());
    _dataLineEdit->setReadOnly(true);

    _widget.show();
}

void Display::SetText(const QString &text)
{
    _dataLineEdit->setText(text);
}

QString Display::GetText() const
{
    return _dataLineEdit->text();
}
