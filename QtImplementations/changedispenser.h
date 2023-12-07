#ifndef CHANGEDISPENSER_H
#define CHANGEDISPENSER_H

#include "Interfaces/IChangeDispenser.h"

class ChangeDispenser : public IChangeDispenser
{
    Q_OBJECT

public:
    void GiveCoin(int valKopecks) override;
};

#endif // CHANGEDISPENSER_H
