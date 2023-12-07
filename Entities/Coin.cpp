#include "Coin.h"


Coin::Coin(int value) :
    _valKopecks(value)
{}

int Coin::GetValKopecks() const
{
    return _valKopecks;
}
