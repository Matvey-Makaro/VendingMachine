#include "numpad.h"

Numpad::Numpad(QWidget* parent) : _numpadWidget(parent)
{
    _numpadWidget.show();

    connect(&_numpadWidget, &NumpadWidget::ButtonClicked, this, &Numpad::onNumpadWidgetButtonClicked);
}

void Numpad::onNumpadWidgetButtonClicked(Buttons btn)
{
    emit ButtonClicked(btn);
}

NumpadWidget* Numpad::GetNumpadWidget()
{
    return &_numpadWidget;
}
