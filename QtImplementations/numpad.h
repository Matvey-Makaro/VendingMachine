#ifndef NUMPAD_H
#define NUMPAD_H

#include "Interfaces/INumpad.h"
#include "numpadwidget.h"

class Numpad : public INumpad
{
    Q_OBJECT

public:
    Numpad(QWidget* parent = nullptr);

    NumpadWidget* GetNumpadWidget();

private slots:
    void onNumpadWidgetButtonClicked(Buttons btn);

private:
    NumpadWidget _numpadWidget;
};
using NumpadShp = QSharedPointer<Numpad>;

#endif // NUMPAD_H
