#pragma once

#include <QVector>

class Coin
{
public:
    Coin(int value = 0);
    int GetValKopecks() const;

private:
    int _valKopecks;
};

using CoinVec = QVector<Coin>;
