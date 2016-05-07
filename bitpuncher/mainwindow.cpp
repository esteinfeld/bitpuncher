#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newpaintdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    lastFrameIndex(0)
{
    clearFrames();

    ui->setupUi(this);

    onActionNew();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::copyCurrentFrame(int target)
{
    for (int row=0 ; row < ui->bitmapCanvas->getRows() ; ++row) {
        for (int col=0 ; col < ui->bitmapCanvas->getCols() ; ++col) {
            mFrames[target][col][row] = ui->bitmapCanvas->getPixel(col, row);
        }
    }
}

void MainWindow::restoreFrame(int source)
{
    for (int row=0 ; row < ui->bitmapCanvas->getRows() ; ++row) {
        for (int col=0 ; col < ui->bitmapCanvas->getCols() ; ++col) {
            ui->bitmapCanvas->setPixel(col, row, mFrames[source][col][row]);
        }
    }
    ui->bitmapCanvas->repaint();
}

void MainWindow::clearFrames()
{
    memset(&mFrames, 0, sizeof(mFrames));
}

void MainWindow::onFrameSliderChanged(int value)
{
    copyCurrentFrame(lastFrameIndex);
    restoreFrame(value);
    lastFrameIndex = value;
    std::cerr << value << std::endl;
}

void MainWindow::onPrevFrameClicked()
{
    if (ui->frameSlider->value() > 0) {
        ui->frameSlider->setValue(ui->frameSlider->value() - 1);
    }
}

void MainWindow::onNextFrameClicked()
{
    if (ui->frameSlider->value() < ui->frameSlider->maximum()) {
        ui->frameSlider->setValue(ui->frameSlider->value() + 1);
    }
}

void MainWindow::onActionNew()
{
    NewPaintDialog dialog(this);
    dialog.setModal(true);

    if (dialog.exec()) {
        clearFrames();
        ui->bitmapCanvas->setSize(dialog.getCols(), dialog.getRows());
        lastFrameIndex = 0;
        ui->frameSlider->setMaximum(dialog.getFrames());
        ui->frameSlider->setValue(0);
    } else {
        std::cerr << "Rejected" << std::endl;
    }
}
