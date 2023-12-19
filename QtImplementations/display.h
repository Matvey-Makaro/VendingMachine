#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

#include "Interfaces/IDisplay.h"

class Display : public IDisplay
{
    Q_OBJECT

public:
    Display(QWidget *parent = nullptr);

    void SetText(const QString& text) override;
    QString GetText() const override;

    QWidget* GetWidget() { return &_widget; }

private:
    QTextEdit* _textEdit;
    QWidget _widget;
};
using DisplayShp = QSharedPointer<Display>;

#endif // DISPLAY_H
