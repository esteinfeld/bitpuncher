#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

#define MAX_FRAMES      200

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onFrameSliderChanged(int);

    void onActionNew();
    void onActionOpen();
    void onActionSave();
    void onActionSaveAs();
    void onActionImport();

    void onPrevFrameClicked();
    void onNextFrameClicked();
    void onClearCurrentFrame();
    void onCopyToNextFrame();
    void onCopyToPrevFrame();

private:
    void copyCurrentFrame(int);
    void restoreFrame(int);
    void initFrames(int, int, int);

    Ui::MainWindow *ui;
    QVector<QImage> mFrames;
    int lastFrameIndex;
    QString currentFile;
    void saveToFile(QString fileName);
    void setCurrentFile(QString fileName);
};

#endif // MAINWINDOW_H
