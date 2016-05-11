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

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

#include "exportwizard.h"

FormatPage::FormatPage(QWidget *parent) : QWizardPage(parent)
{
    setTitle("Export format selection");

    QGroupBox *formatBox = new QGroupBox;
    formatBox->setTitle("Export format");

    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(formatBox);
    setLayout(vbl);

    QRadioButton *radioPng = new QRadioButton(formatBox);
    radioPng->setText("PNG");
    radioPng->setChecked(true);

    QRadioButton *radioCHeader = new QRadioButton(formatBox);
    radioCHeader->setText("C Header");

    QVBoxLayout *vblBox = new QVBoxLayout;
    vblBox->addWidget(radioPng);
    vblBox->addWidget(radioCHeader);

    formatBox->setLayout(vblBox);

    registerField("isPng", radioPng, "checked");
}


PathPage::PathPage(QWidget *parent) : QWizardPage(parent)
{
    path = new QLineEdit;
    QPushButton *browseButton = new QPushButton;
    browseButton->setText("Browse..");
    QObject::connect(browseButton, SIGNAL(pressed()), SLOT(onBrowsePressed()));

    QHBoxLayout *hbl1 = new QHBoxLayout;
    hbl1->addWidget(path);
    hbl1->addWidget(browseButton);

    QGroupBox *rangeBox = new QGroupBox;
    rangeBox->setTitle("Export range");

    QRadioButton *radioEntire = new QRadioButton(rangeBox);
    radioEntire->setText("Entire sequence");
    radioEntire->setChecked(true);

    QRadioButton *radioCurrent = new QRadioButton(rangeBox);
    radioCurrent->setText("Current frame");

    QVBoxLayout *boxvbl = new QVBoxLayout;
    boxvbl->addWidget(radioEntire);
    boxvbl->addWidget(radioCurrent);
    rangeBox->setLayout(boxvbl);

    cbOverwrite = new QCheckBox;
    cbOverwrite->setText("Overwrite existing files");

    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addLayout(hbl1);
    vbl->addWidget(rangeBox);
    vbl->addWidget(cbOverwrite);
    setLayout(vbl);

    registerField("path*", path);
    registerField("isEntire", radioEntire, "checked");
    registerField("allowOverwrite", cbOverwrite, "checked");
}

void PathPage::initializePage()
{
    if (field("isPng").toBool()) {
        setTitle("Output path");
        cbOverwrite->setEnabled(true);
    } else {
        setTitle("Output file");
        cbOverwrite->setEnabled(false);
    }
}

void PathPage::onBrowsePressed()
{
    QString fileName;

    if (field("isPng").toBool()) {
        fileName = QFileDialog::getExistingDirectory(this, "Export output directory",
                                                     QDir::homePath(), QFileDialog::ShowDirsOnly);
    } else {
        fileName = QFileDialog::getSaveFileName(this, "Export output file",
                                                QDir::homePath(), "(Header file *.h)");
    }

    if (fileName == "") {
        return;
    }

    path->setText(fileName);
}


ExportWizard::ExportWizard(QVector<QImage> &frames, int currentFrame, QWidget *parent) :
    QWizard(parent),
    mFrames(frames),
    mCurrentFrame(currentFrame)
{
    addPage(new FormatPage);
    addPage(new PathPage);

    setWindowTitle("Export animation");
    setFixedSize(600, 400);
}

void ExportWizard::accept()
{
    if (field("isPng").toBool()) {
        exportPng();
    } else {
        exportCHeader();
    }

    QWizard::accept();
}

void ExportWizard::exportPng()
{
    // TODO: honour the overwrite
    QDir saveDir(field("path").toString());
    QVectorIterator<QImage> i(mFrames);
    int index = 0;

    while (i.hasNext()) {
        QString fileName = QString("bpexport-%1.png").arg(index, 3, 10, QLatin1Char('0'));
        i.next().save(saveDir.filePath(fileName));
        ++index;
    }
}

void ExportWizard::exportCHeader()
{
    // TODO: implementation!
}
