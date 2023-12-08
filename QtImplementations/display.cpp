#include "display.h"

Display::Display(QWidget *parent) : _widget(parent)
{
    _widget.setWindowTitle("Display");
    _widget.setFixedSize(300, 100);

    _textEdit = new QTextEdit(&_widget);
    _textEdit->resize(_widget.size());
    _textEdit->setReadOnly(true);

    _widget.show();
}

void Display::SetText(const QString &text)
{
    _textEdit->setText(text);
}

QString Display::GetText() const
{
    return _textEdit->toPlainText();
}
