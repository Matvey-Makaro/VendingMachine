#ifndef CARDREADERWIDGET_H
#define CARDREADERWIDGET_H

#include <QWidget>

#include "Types.h"

namespace Ui {
class CardReaderWidget;
}

class CardReaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CardReaderWidget(QWidget *parent = nullptr);
    ~CardReaderWidget();

    void SetPrice(MoneyAmount price);
    void Enable();
    void Cancel();

signals:
    void Enabled();
    void Paid();

private slots:
    void on_btnEnable_clicked();

    void on_btnPayWithCard_clicked();

private:
    Ui::CardReaderWidget *ui;
};

#endif // CARDREADERWIDGET_H
