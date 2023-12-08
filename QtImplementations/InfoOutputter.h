#pragma once

#include <QSharedPointer>
#include <QString>
#include "Interfaces/IInfoOutputter.h"

class InfoOutputter : public IInfoOutputter
{
public:
    InfoOutputter() = default;

    void Output(Messages msg) override;

private:
    QString ToText(Messages msg) const;
};
using InfoOutputterShp = QSharedPointer<InfoOutputter>;
