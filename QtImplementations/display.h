#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

#include "Interfaces/IDisplay.h"

class Display : public IDisplay
{
    Q_OBJECT

public:
    Display(QWidget *parent = nullptr);

    void SetText(const QString& text) override;
    QString GetText() const override;

private:
    QLineEdit* _dataLineEdit;
    QWidget _widget;
};

#endif // DISPLAY_H
