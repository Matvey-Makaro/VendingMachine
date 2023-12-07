#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "QtImplementations/display.h"
#include "QtImplementations/numpad.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Display* display = new Display();
    display->SetText("hello world");

    Numpad* numpad = new Numpad();
    connect(numpad, &Numpad::ButtonClicked, [](Buttons btn) { qDebug() << static_cast<int>(btn) << " CLICKED\n"; });
}

MainWindow::~MainWindow()
{
    delete ui;
}

