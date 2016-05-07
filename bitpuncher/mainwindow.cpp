#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QIODevice>

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

    if (value > 0) {
        ui->copyToPrev->setEnabled(true);
    } else {
        ui->copyToPrev->setEnabled(false);
    }

    if (value == ui->frameSlider->maximum()) {
        ui->copyToNext->setEnabled(false);
    } else {
        ui->copyToNext->setEnabled(true);
    }

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

        ui->copyToPrev->setEnabled(false);
        ui->copyToNext->setEnabled(true);
    } else {
        std::cerr << "Rejected" << std::endl;
    }
}

void MainWindow::onActionOpen()
{
    QFile file("/Users/xi/Desktop/merda.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    quint32 magic;
    in >> magic;

    if (magic != 0xDEADBEEF) {
        std::cerr << "File is corrupted" << std::endl;
        return;
    }

    in.setVersion(QDataStream::Qt_4_0);

    int cols, rows, framesCount;
    in >> cols;
    in >> rows;
    in >> framesCount;
    //in >> mFrames;

    /*
    ui->bitmapCanvas->setSize(cols, rows);
    lastFrameIndex = 0;
    ui->frameSlider->setMaximum(dialog.getFrames());
    ui->frameSlider->setValue(0);

    ui->copyToPrev->setEnabled(false);
    ui->copyToNext->setEnabled(true);
    */

    std::cerr << "Imported " << framesCount << " frames" << std::endl;
}

void MainWindow::onActionSave()
{
    QFile file("/Users/xi/Desktop/merda.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    out << (quint32)0xDEADBEEF;
    out << ui->bitmapCanvas->getCols();
    out << ui->bitmapCanvas->getRows();
    out << ui->frameSlider->maximum();
    //out << mFrames;

    out.setVersion(QDataStream::Qt_4_0);
}

void MainWindow::onClearCurrentFrame()
{
    ui->bitmapCanvas->clear();
    copyCurrentFrame(lastFrameIndex);
    ui->bitmapCanvas->repaint();
}

void MainWindow::onCopyToNextFrame()
{
    copyCurrentFrame(ui->frameSlider->value() + 1);
}

void MainWindow::onCopyToPrevFrame()
{
    copyCurrentFrame(ui->frameSlider->value() - 1);
}
