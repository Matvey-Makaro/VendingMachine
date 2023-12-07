#include "Banknote.h"

Banknote::Banknote(int value) :
    _valKopecks(value)
{}

int Banknote::GetValKopecks() const
{
    return _valKopecks;
}
