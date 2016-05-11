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
    void onActionExport();

    void onPrevFrameClicked();
    void onNextFrameClicked();
    void onClearCurrentFrame();
    void onCopyToNextFrame();
    void onCopyToPrevFrame();

private:
    virtual void closeEvent(QCloseEvent *);
    void copyCurrentFrame(int);
    void restoreFrame(int);
    void initFrames(int, int, int);
    void saveToFile(QString fileName);
    void setCurrentFile(QString fileName);

    Ui::MainWindow *ui;
    QVector<QImage> mFrames;
    int lastFrameIndex;
    QString currentFile;
    bool isDirty;

private slots:
    void setDirty();
};

#endif // MAINWINDOW_H
