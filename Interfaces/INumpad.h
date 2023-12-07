#pragma once

#include <QObject>
#include "IDevice.h"

enum class Buttons
{
    Num0 = 0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    OK,
    Del,
    Change
};

class INumpad : public IDevice
{
    Q_OBJECT
public:
    virtual ~INumpad() = default;

signals:
    void ButtonClicked(Buttons);
};
using INumpadShp = QSharedPointer<INumpad>;
