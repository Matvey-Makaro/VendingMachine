QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entities/Banknote.cpp \
    Entities/Coin.cpp \
    QtImplementations/dispenser.cpp \
    QtImplementations/display.cpp \
    QtImplementations/numpad.cpp \
    main.cpp \
    MainWindow.cpp \
    QtImplementations/numpadwidget.cpp

HEADERS += \
    Entities/Banknote.h \
    Entities/Coin.h \
    Interfaces/IBanknoteReceiver.h \
    Interfaces/ICardReader.h \
    Interfaces/IChangeDispenser.h \
    Interfaces/ICoinReceiver.h \
    Interfaces/IDevice.h \
    Interfaces/IDispenser.h \
    Interfaces/IDisplay.h \
    Interfaces/INumpad.h \
    MainWindow.h \
    QtImplementations/dispenser.h \
    QtImplementations/display.h \
    QtImplementations/numpad.h \
    Types.h \
    QtImplementations/numpadwidget.h

FORMS += \
    MainWindow.ui \
    QtImplementations/numpadwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QtImplementations/фюфщвл
