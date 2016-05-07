#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QFileDialog>
#include <QDir>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newpaintdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    lastFrameIndex(0)
{
    ui->setupUi(this);

    onActionNew();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::copyCurrentFrame(int target)
{
    mFrames[target] = QImage(ui->bitmapCanvas->getBitmap());
}

void MainWindow::restoreFrame(int source)
{
    ui->bitmapCanvas->setBitmap(mFrames[source]);
    ui->bitmapCanvas->repaint();
}

void MainWindow::initFrames(int count, int cols, int rows)
{
    mFrames.clear();

    for (int i=0 ; i < count ; ++i) {
        QImage img(cols, rows, QImage::Format_Mono);
        img.fill(0);
        mFrames.append(img);
    }

    std::cerr << "Init'd " << mFrames.count() << " frames";
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
        initFrames(dialog.getFrames(), dialog.getCols(), dialog.getRows());
        ui->bitmapCanvas->setSize(dialog.getCols(), dialog.getRows());
        lastFrameIndex = 0;
        ui->frameSlider->setMaximum(dialog.getFrames() - 1);
        ui->frameSlider->setValue(0);

        ui->copyToPrev->setEnabled(false);
        ui->copyToNext->setEnabled(true);
    } else {
        std::cerr << "Rejected" << std::endl;
    }
}

void MainWindow::onActionOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open BitPuncher data file",
                                                    QDir::homePath(), "BitPuncher data files (*.bpd)");

    if (fileName == "") {
        return;
    }

    QFile file(fileName);

    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    quint32 magic;
    in >> magic;

    if (magic != 0xDEADBEEF) {
        std::cerr << "File is corrupted" << std::endl;
        return;
    }

    in.setVersion(QDataStream::Qt_4_0);

    int cols, rows, maxIndex;
    in >> cols;
    in >> rows;
    in >> maxIndex;
    in >> mFrames;

    ui->bitmapCanvas->setSize(cols, rows);
    lastFrameIndex = 0;
    ui->frameSlider->setMaximum(maxIndex);
    ui->frameSlider->setValue(0);
    restoreFrame(0);

    ui->copyToPrev->setEnabled(false);
    ui->copyToNext->setEnabled(true);

    statusBar()->showMessage("Successfully loaded " + QString::number(maxIndex + 1) +
                             " frames from " + fileName, 20000);
}

void MainWindow::onActionSave()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save BitPuncher data file",
                                                    QDir::homePath(), "BitPuncher data files (*.bpd)");

    if (fileName == "") {
        return;
    }

    QFile file(fileName);

    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    copyCurrentFrame(lastFrameIndex);

    out << (quint32)0xDEADBEEF;
    out << ui->bitmapCanvas->getCols();
    out << ui->bitmapCanvas->getRows();
    out << ui->frameSlider->maximum();
    out << mFrames;

    out.setVersion(QDataStream::Qt_4_0);

    statusBar()->showMessage("Successfully saved " + QString::number(ui->frameSlider->maximum() + 1) +
                             " frames to " + fileName, 20000);
}

void MainWindow::onClearCurrentFrame()
{
    ui->bitmapCanvas->clear();
    copyCurrentFrame(lastFrameIndex);
    ui->bitmapCanvas->repaint();
}

void MainWindow::onCopyToNextFrame()
{
    int newIndex = ui->frameSlider->value() + 1;
    copyCurrentFrame(newIndex);
    ui->frameSlider->setValue(newIndex);
}

void MainWindow::onCopyToPrevFrame()
{
    int newIndex = ui->frameSlider->value() - 1;
    copyCurrentFrame(newIndex);
    ui->frameSlider->setValue(newIndex);
}
