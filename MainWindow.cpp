#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "QtImplementations/display.h"
#include "QtImplementations/numpad.h"
#include "QtImplementations/dispenser.h"
#include "QtImplementations/coinreceiver.h"
#include "QtImplementations/banknotereceiver.h"
#include "QtImplementations/changedispenser.h"
#include "QtImplementations/cardreader.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->hide();

    IDisplay* display = new Display();
    display->SetText("hello world");

    INumpad* numpad = new Numpad();
    connect(numpad, &Numpad::ButtonClicked, [](Buttons btn) { qDebug() << static_cast<int>(btn) << " CLICKED\n"; });

    IDispenser* dispenser = new Dispenser();
    IChangeDispenser* chDispenser = new ChangeDispenser();
    chDispenser->GiveCoin(50);
//    dispenser->GiveItem(3);

    ICoinReceiver* coinReceiver = new CoinReceiver();
    connect(coinReceiver, &CoinReceiver::CoinReceived, [](const Coin& coin)
    {
        qDebug() << "COIN RECEIVED: " << coin.GetValKopecks() << "\n";
    });

    IBanknoteReceiver* bnReceiver = new BanknoteReceiver();
    connect(bnReceiver, &BanknoteReceiver::BanknoteReceived, [](const Banknote& b)
    {
        qDebug() << "BANKNOTE RECEIVED: " << b.GetValRubles() << "\n";
    });

    ICardReader* cardReader = new CardReader();
    cardReader->SetPrice(315);
    connect(cardReader, &ICardReader::Enabled, []()
    {
        qDebug() << "CARD READER: ENABLED\n";
    });
    connect(cardReader, &ICardReader::Paid, []()
    {
        qDebug() << "CARD READER: PAID\n";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

