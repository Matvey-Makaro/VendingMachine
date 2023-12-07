#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "QtImplementations/display.h"
#include "QtImplementations/numpad.h"
#include "QtImplementations/dispenser.h"
#include "QtImplementations/coinreceiver.h"
#include "QtImplementations/banknotereceiver.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->hide();

    Display* display = new Display();
    display->SetText("hello world");

    Numpad* numpad = new Numpad();
    connect(numpad, &Numpad::ButtonClicked, [](Buttons btn) { qDebug() << static_cast<int>(btn) << " CLICKED\n"; });

    Dispenser* dispenser = new Dispenser();
//    dispenser->GiveItem(3);

    CoinReceiver* coinReceiver = new CoinReceiver();
    connect(coinReceiver, &CoinReceiver::CoinReceived, [](const Coin& coin)
    {
        qDebug() << "COIN RECEIVED: " << coin.GetValKopecks() << "\n";
    });

    BanknoteReceiver* bnReceiver = new BanknoteReceiver();
    connect(bnReceiver, &BanknoteReceiver::BanknoteReceived, [](const Banknote& b)
    {
        qDebug() << "BANKNOTE RECEIVED: " << b.GetValRubles() << "\n";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

