#include "newpaintdialog.h"
#include "ui_newpaintdialog.h"

NewPaintDialog::NewPaintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPaintDialog)
{
    ui->setupUi(this);
}

NewPaintDialog::~NewPaintDialog()
{
    delete ui;
}

int NewPaintDialog::getRows()
{
    return ui->rows->value();
}
