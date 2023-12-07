#pragma once

#include <QString>
#include <QSharedPointer>

struct AppConfig
{
    QString serverHost;
    int serverPort;
    int numOfItemDisplayes;
};
using AppConfigShp = QSharedPointer<AppConfig>;
