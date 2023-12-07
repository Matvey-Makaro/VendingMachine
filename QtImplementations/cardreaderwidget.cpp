#include "cardreaderwidget.h"
#include "ui_cardreaderwidget.h"

CardReaderWidget::CardReaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardReaderWidget)
{
    ui->setupUi(this);

    Cancel();
}

CardReaderWidget::~CardReaderWidget()
{
    delete ui;
}

void CardReaderWidget::SetPrice(MoneyAmount price)
{
    int rubles = price / 100;
    int kopecks = price % 100;

    ui->sumLabel->setText(tr("%1 рублей, %2 копеек").arg(rubles).arg(kopecks));
}

void CardReaderWidget::Enable()
{
    ui->btnPayWithCard->setEnabled(true);
    ui->sumTextLabel->show();
    ui->sumLabel->show();
}

void CardReaderWidget::Cancel()
{
    ui->btnPayWithCard->setEnabled(false);
    ui->sumTextLabel->hide();
    ui->sumLabel->hide();
}

void CardReaderWidget::on_btnEnable_clicked()
{
    Enable();
    emit Enabled();
}

void CardReaderWidget::on_btnPayWithCard_clicked()
{
    Cancel();
    emit Paid();
}
