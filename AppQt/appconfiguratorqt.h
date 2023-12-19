#ifndef APPCONFIGURATORQT_H
#define APPCONFIGURATORQT_H

#include "App/AppConfigurator.h"
#include "MainWindow.h"

class AppConfiguratorQt : public AppConfigurator
{
public:
    using AppConfigurator::AppConfigurator;

    VendingMachineDevicesShp CreateDevices() override;

private:
    MainWindow _mainWindow;
};

#endif // APPCONFIGURATORQT_H
