#pragma once

#include <QObject>
#include <QString>
#include "IDevice.h"

class IDisplay : public IDevice
{
    Q_OBJECT
public:
    virtual ~IDisplay() = default;

    virtual void SetText(const QString& text) = 0;
    virtual QString GetText() const = 0;
};
using IDisplayShp = QSharedPointer<IDisplay>;
