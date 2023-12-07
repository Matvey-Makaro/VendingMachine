#ifndef BANKNOTERECEIVERWIDGET_H
#define BANKNOTERECEIVERWIDGET_H

#include <QWidget>

#include "Entities/Banknote.h"

namespace Ui {
class BanknoteReceiverWidget;
}

class BanknoteReceiverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BanknoteReceiverWidget(QWidget *parent = nullptr);
    ~BanknoteReceiverWidget();

signals:
    void BanknoteReceived(const Banknote&);

private slots:
    void on_btn5rubles_clicked();

    void on_btn20rubles_clicked();

    void on_btn10rubles_clicked();

private:
    Ui::BanknoteReceiverWidget *ui;
};
using BanknoteReceiverWidgetShp = QSharedPointer<BanknoteReceiverWidget>;

#endif // BANKNOTERECEIVERWIDGET_H
