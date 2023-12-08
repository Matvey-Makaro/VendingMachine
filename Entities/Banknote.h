#pragma once

#include <QVector>

class Banknote
{
public:
    Banknote(int value = 0);

    int GetValKopecks() const;

private:
    int _valKopecks;
};

using BanknoteVec = QVector<Banknote>;
