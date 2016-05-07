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

#include <QFileDialog>

#include "exportdialog.h"
#include "ui_exportdialog.h"

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

QString ExportDialog::getFormat()
{
    return ui->format->currentText();
}

void ExportDialog::onFolderSelectButtonPressed()
{
    QString fileName = QFileDialog::getExistingDirectory(this, "Export output directory",
                                                    QDir::homePath(), QFileDialog::ShowDirsOnly);

    if (fileName == "") {
        return;
    }

    ui->folderButton->setText(fileName);
    ui->buttonOk->setEnabled(true);
    ui->buttonOk->setFocus();
}
