QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    App/AppConfig.cpp \
    App/AppConfigReader.cpp \
    App/AppConfigurator.cpp \
    App/database.cpp \
    BLL/VendingMachine.cpp \
    BLL/VendingMachineDevices.cpp \
    Entities/Banknote.cpp \
    Entities/Coin.cpp \
    Entities/Item.cpp \
    QtImplementations/InfoOutputter.cpp \
    QtImplementations/banknotereceiver.cpp \
    QtImplementations/banknotereceiverwidget.cpp \
    QtImplementations/cardreader.cpp \
    QtImplementations/cardreaderwidget.cpp \
    QtImplementations/changedispenser.cpp \
    QtImplementations/coinreceiver.cpp \
    QtImplementations/coinreceiverwidget.cpp \
    QtImplementations/dispenser.cpp \
    QtImplementations/display.cpp \
    QtImplementations/numpad.cpp \
    main.cpp \
    MainWindow.cpp \
    QtImplementations/numpadwidget.cpp

HEADERS += \
    App/AppConfig.h \
    App/AppConfigReader.h \
    App/AppConfigurator.h \
    App/database.h \
    BLL/VendingMachine.h \
    BLL/VendingMachineDevices.h \
    Entities/Banknote.h \
    Entities/Coin.h \
    Entities/Item.h \
    Entities/Slot.h \
    Entities/Messages.h \
    Interfaces/IBanknoteReceiver.h \
    Interfaces/ICardReader.h \
    Interfaces/IChangeDispenser.h \
    Interfaces/ICoinReceiver.h \
    Interfaces/IDevice.h \
    Interfaces/IDispenser.h \
    Interfaces/IDisplay.h \
    Interfaces/IInfoOutputter.h \
    Interfaces/INumpad.h \
    MainWindow.h \
    QtImplementations/InfoOutputter.h \
    QtImplementations/banknotereceiver.h \
    QtImplementations/banknotereceiverwidget.h \
    QtImplementations/cardreader.h \
    QtImplementations/cardreaderwidget.h \
    QtImplementations/changedispenser.h \
    QtImplementations/coinreceiver.h \
    QtImplementations/coinreceiverwidget.h \
    QtImplementations/dispenser.h \
    QtImplementations/display.h \
    QtImplementations/numpad.h \
    Types.h \
    QtImplementations/numpadwidget.h

FORMS += \
    MainWindow.ui \
    QtImplementations/banknotereceiverwidget.ui \
    QtImplementations/cardreaderwidget.ui \
    QtImplementations/coinreceiverwidget.ui \
    QtImplementations/numpadwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QtImplementations/фюфщвл
