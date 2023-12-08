#pragma once

#include <QString>
#include "AppConfig.h"

class AppConfigReader
{
public:
    AppConfigReader() = default;
    AppConfigShp Read(const QString& fname);
};

