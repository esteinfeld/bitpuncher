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
