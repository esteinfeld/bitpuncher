#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newpaintdialog.h"

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

void MainWindow::onFrameSliderChanged(int value)
{
    std::cerr << value << std::endl;
}

void MainWindow::onActionNew()
{
    NewPaintDialog dialog(this);
    dialog.setModal(true);
    if (dialog.exec()) {
        std::cerr << "Exiting now " << dialog.getRows() << std::endl;
    } else {
        std::cerr << "Rejected" << std::endl;
    }

}
