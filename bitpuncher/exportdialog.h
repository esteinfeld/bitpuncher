#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = 0);
    ~ExportDialog();

    QString getFormat();
    QString getOutputFolder();

public slots:
    void onFolderSelectButtonPressed();

private:
    Ui::ExportDialog *ui;
};

#endif // EXPORTDIALOG_H
