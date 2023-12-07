#include "coinreceiverwidget.h"
#include "ui_coinreceiverwidget.h"

CoinReceiverWidget::CoinReceiverWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoinReceiverWidget)
{
    ui->setupUi(this);
}

CoinReceiverWidget::~CoinReceiverWidget()
{
    delete ui;
}

void CoinReceiverWidget::on_btn10kopecks_clicked()
{
    emit CoinReceived(Coin(10));
}

void CoinReceiverWidget::on_btn1kopeck_clicked()
{

    emit CoinReceived(Coin(1));
}

void CoinReceiverWidget::on_btn1ruble_clicked()
{

    emit CoinReceived(Coin(100));
}

void CoinReceiverWidget::on_btn20kopecks_clicked()
{

    emit CoinReceived(Coin(20));
}

void CoinReceiverWidget::on_btn2kopecks_clicked()
{

    emit CoinReceived(Coin(2));
}

void CoinReceiverWidget::on_btn2rubles_clicked()
{

    emit CoinReceived(Coin(200));
}

void CoinReceiverWidget::on_btn50kopecks_clicked()
{

    emit CoinReceived(Coin(50));
}

void CoinReceiverWidget::on_btn5kopecks_clicked()
{

    emit CoinReceived(Coin(5));
}
