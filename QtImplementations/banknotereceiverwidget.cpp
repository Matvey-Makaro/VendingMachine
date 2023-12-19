#include "banknotereceiverwidget.h"
#include "ui_banknotereceiverwidget.h"

#include "Entities/Banknote.h"

BanknoteReceiverWidget::BanknoteReceiverWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BanknoteReceiverWidget)
{
    ui->setupUi(this);
}

BanknoteReceiverWidget::~BanknoteReceiverWidget()
{
    delete ui;
}

void BanknoteReceiverWidget::on_btn5rubles_clicked()
{
    emit BanknoteReceived(Banknote(500));
}

void BanknoteReceiverWidget::on_btn10rubles_clicked()
{
    emit BanknoteReceived(Banknote(1000));
}

void BanknoteReceiverWidget::on_btn20rubles_clicked()
{
    emit BanknoteReceived(Banknote(2000));
}
