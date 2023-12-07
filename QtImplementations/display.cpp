#include "display.h"

Display::Display(QWidget *parent)
    : _widget(parent)
{
    _widget.setWindowTitle("Display");
    _dataLabel = new QLabel(&_widget);
    _dataLabel->setText("aojfigkwdo");
    _dataLabel->move(50, 50);
}

void Display::SetText(const QString &text)
{
    _dataLabel->setText(text);
}

QString Display::GetText() const
{
    return _dataLabel->text();
}
