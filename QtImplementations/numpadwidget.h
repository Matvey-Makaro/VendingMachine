#ifndef NUMPADWIDGET_H
#define NUMPADWIDGET_H

#include <QWidget>

enum class Buttons;

namespace Ui {
class NumpadWidget;
}

class NumpadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NumpadWidget(QWidget *parent = nullptr);
    ~NumpadWidget();

signals:
    void ButtonClicked(Buttons);

private slots:
    void on_btn0_clicked();

    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

    void on_btn9_clicked();

    void on_btnChange_clicked();

    void on_btndel_clicked();

    void on_btnOk_clicked();

private:
    Ui::NumpadWidget *ui;
};

#endif // NUMPADWIDGET_H
