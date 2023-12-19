#include "numpadwidget.h"
#include "ui_numpadwidget.h"

#include "Interfaces/INumpad.h"

#include <QDebug>

NumpadWidget::NumpadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumpadWidget)
{
    ui->setupUi(this);
}

NumpadWidget::~NumpadWidget()
{
    delete ui;
}

void NumpadWidget::on_btn0_clicked()
{
    emit ButtonClicked(Buttons::Num0);
}

void NumpadWidget::on_btn1_clicked()
{
    emit ButtonClicked(Buttons::Num1);
}

void NumpadWidget::on_btn2_clicked()
{
    emit ButtonClicked(Buttons::Num2);
}

void NumpadWidget::on_btn3_clicked()
{

    emit ButtonClicked(Buttons::Num3);
}

void NumpadWidget::on_btn4_clicked()
{

    emit ButtonClicked(Buttons::Num4);
}

void NumpadWidget::on_btn5_clicked()
{

    emit ButtonClicked(Buttons::Num5);
}

void NumpadWidget::on_btn6_clicked()
{

    emit ButtonClicked(Buttons::Num6);
}

void NumpadWidget::on_btn7_clicked()
{

    emit ButtonClicked(Buttons::Num7);
}

void NumpadWidget::on_btn8_clicked()
{

    emit ButtonClicked(Buttons::Num8);
}

void NumpadWidget::on_btn9_clicked()
{

    emit ButtonClicked(Buttons::Num9);
}

void NumpadWidget::on_btnChange_clicked()
{

    emit ButtonClicked(Buttons::Change);
}

void NumpadWidget::on_btndel_clicked()
{

    emit ButtonClicked(Buttons::Del);
}

void NumpadWidget::on_btnOk_clicked()
{

    emit ButtonClicked(Buttons::OK);
}
