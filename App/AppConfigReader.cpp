#include "AppConfigReader.h"

AppConfigShp AppConfigReader::Read(const QString& fname)
{
    // TODO: Impl...
    auto cfg = AppConfigShp::create();
    cfg->serverHost = "local";
    cfg->serverPort = 8000;
    cfg->numOfItemDisplayes = 25;
    return cfg;
}
