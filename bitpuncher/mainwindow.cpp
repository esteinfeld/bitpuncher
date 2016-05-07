#include <QGraphicsView>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->bitmapCanvas->setSize(40, 10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

