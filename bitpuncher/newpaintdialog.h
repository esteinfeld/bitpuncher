#ifndef NEWPAINTDIALOG_H
#define NEWPAINTDIALOG_H

#include <QDialog>

namespace Ui {
class NewPaintDialog;
}

class NewPaintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPaintDialog(QWidget *parent = 0);
    ~NewPaintDialog();

    int getRows();

private:
    Ui::NewPaintDialog *ui;
};

#endif // NEWPAINTDIALOG_H
