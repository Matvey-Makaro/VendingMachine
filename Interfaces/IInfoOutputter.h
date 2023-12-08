#pragma once

#include "Entities/Messages.h"
#include "IDevice.h"



class IInfoOutputter : public IDevice
{
    Q_OBJECT
public:
    // TODO: Change to Output info, warnings and errors
    virtual void Output(Messages msg) = 0;

};
using IInfoOutputterShp = QSharedPointer<IInfoOutputter>;
