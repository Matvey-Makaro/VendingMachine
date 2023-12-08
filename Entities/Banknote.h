#pragma once

#include <QVector>

class Banknote
{
public:
    Banknote(int value);

    int GetValKopecks() const;

private:
    int _valKopecks;
};

using BanknoteVec = QVector<Banknote>;
