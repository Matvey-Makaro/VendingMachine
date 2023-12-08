#pragma once

#include <QObject>

#include <QSharedPointer>

class IDevice : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
    virtual ~IDevice() = default;

signals:
    void ErrorOccured(int);
};
using IDeviceShp = QSharedPointer<IDevice>;
