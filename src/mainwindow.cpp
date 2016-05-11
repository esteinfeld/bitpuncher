/*
    bitpuncher - monochrome bitmap editor

    Copyright (C) 2016  OXullo Intersecans <x@brainrapers.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QCloseEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newpaintdialog.h"
#include "exportdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    lastFrameIndex(0),
    isDirty(false)
{
    ui->setupUi(this);

    QObject::connect(ui->bitmapCanvas, SIGNAL(canvasModified()), this, SLOT(setDirty()));

    // TODO: prevent the initial dialog to abort, it'd leave a bunch of uninitialised members
    onActionNew();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDirty()
{
    isDirty = true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    std::cerr << "closeEvent" << std::endl;

    if (isDirty) {
        QMessageBox warning;
        warning.setText("The canvas has been modified");
        warning.setInformativeText("Do you want to save the changes?");
        warning.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        warning.setDefaultButton(QMessageBox::Save);
        warning.setIcon(QMessageBox::Warning);

        switch (warning.exec()) {
            case QMessageBox::Save:
                onActionSave();
                event->accept();
                break;

            case QMessageBox::Discard:
                event->accept();
                break;

            case QMessageBox::Cancel:
                event->ignore();
                break;
        }
    } else {
        event->accept();
    }

    isDirty = false;
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

    if (dialog.exec() == NewPaintDialog::Rejected) {
        return;
    }

    initFrames(dialog.getFrames(), dialog.getCols(), dialog.getRows());
    ui->bitmapCanvas->setSize(dialog.getCols(), dialog.getRows());
    lastFrameIndex = 0;
    ui->frameSlider->setMaximum(dialog.getFrames() - 1);
    ui->frameSlider->setValue(0);

    ui->copyToPrev->setEnabled(false);
    if (dialog.getFrames() > 1) {
        ui->copyToNext->setEnabled(true);
    } else {
        ui->copyToNext->setEnabled(false);
    }

    setCurrentFile("");
    statusBar()->clearMessage();
}

void MainWindow::setCurrentFile(QString fileName)
{
    currentFile = fileName;
    if (fileName != "") {
        setWindowTitle("BitPuncher (" + fileName + ")");
    } else {
        setWindowTitle("BitPuncher");
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
        QMessageBox errorDialog;
        errorDialog.setText("Cannot open file " + fileName + ": bad magic");
        errorDialog.setIcon(QMessageBox::Critical);
        errorDialog.exec();
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

    setCurrentFile(fileName);

    statusBar()->showMessage("Successfully loaded " + QString::number(maxIndex + 1) +
                             " frames from " + fileName, 5000);
}

void MainWindow::saveToFile(QString fileName)
{
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
                             " frames to " + fileName, 5000);

    isDirty = false;
}

void MainWindow::onActionSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save BitPuncher data file",
                                                    QDir::homePath(), "BitPuncher data files (*.bpd)");

    if (fileName == "") {
        return;
    }

    saveToFile(fileName);

    setCurrentFile(fileName);
}

void MainWindow::onActionSave()
{
    if (currentFile != "") {
        saveToFile(currentFile);
    } else {
        onActionSaveAs();
    }
}

void MainWindow::onActionImport()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open image", QDir::homePath(),
                                                    "Images (*.png *.xpm *.jpg)");

    QImage img;
    img.load(fileName);

    if (img.size().width() != ui->bitmapCanvas->getCols() ||
            img.size().height() != ui->bitmapCanvas->getRows()) {
        QImage scaled = img.scaled(ui->bitmapCanvas->getCols(), ui->bitmapCanvas->getRows());
        img = scaled;

        QMessageBox warning;
        warning.setText("Warning: the source has been scaled to the current project size");
        warning.setIcon(QMessageBox::Warning);
        warning.exec();
    }

    QImage converted = img.convertToFormat(QImage::Format_Mono);
    img = converted;
    ui->bitmapCanvas->setBitmap(img);
    ui->bitmapCanvas->repaint();
}

void MainWindow::onActionExport()
{
    ExportDialog dialog(this);

    if (dialog.exec() == NewPaintDialog::Rejected) {
        return;
    }

    if (dialog.getFormat() == "PNG") {
        QDir saveDir(dialog.getOutputFolder());
        QVectorIterator<QImage> i(mFrames);
        int index = 0;

        while (i.hasNext()) {
            QString fileName = QString("bpexport-%1.png").arg(index, 3, 10, QLatin1Char('0'));
            i.next().save(saveDir.filePath(fileName));
            ++index;
        }
    }
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
