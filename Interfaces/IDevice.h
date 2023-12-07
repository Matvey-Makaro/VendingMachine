#pragma once

#include <QObject>

class IDevice : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
    virtual ~IDevice() = default;

signals:
    void ErrorOccured(int);
};
