#ifndef NUMPAD_H
#define NUMPAD_H

#include "Interfaces/INumpad.h"
#include "numpadwidget.h"

class Numpad : public INumpad
{
    Q_OBJECT

public:
    Numpad(QWidget* parent = nullptr);

private slots:
    void onNumpadWidgetButtonClicked(Buttons btn);

private:
    NumpadWidget _numpadWidget;
};

#endif // NUMPAD_H
