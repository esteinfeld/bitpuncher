#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "bitmapcanvas.h"

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
    void onPrevFrameClicked();
    void onNextFrameClicked();

private:
    void copyCurrentFrame(int);
    void restoreFrame(int);
    void clearFrames();

    Ui::MainWindow *ui;
    bool mFrames[MAX_FRAMES][MAX_COLS][MAX_ROWS];
    int lastFrameIndex;
};

#endif // MAINWINDOW_H
