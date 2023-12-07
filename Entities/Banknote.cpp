#include "Banknote.h"

Banknote::Banknote(int value) :
    _valRubles(value)
{}

int Banknote::GetValRubles() const
{
    return _valRubles;
}
