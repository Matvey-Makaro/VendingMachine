#ifndef COINRECEIVERWIDGET_H
#define COINRECEIVERWIDGET_H

#include <QWidget>

#include "Entities/Coin.h"

namespace Ui {
class CoinReceiverWidget;
}

class CoinReceiverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoinReceiverWidget(QWidget *parent = nullptr);
    ~CoinReceiverWidget();

signals:
    void CoinReceived(const Coin& coin);

private slots:
    void on_btn10kopecks_clicked();

    void on_btn1kopeck_clicked();

    void on_btn1ruble_clicked();

    void on_btn20kopecks_clicked();

    void on_btn2kopecks_clicked();

    void on_btn2rubles_clicked();

    void on_btn50kopecks_clicked();

    void on_btn5kopecks_clicked();

private:
    Ui::CoinReceiverWidget *ui;
};
using CoinReceiverWidgetShp = QSharedPointer<CoinReceiverWidget>;

#endif // COINRECEIVERWIDGET_H
