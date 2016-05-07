#ifndef BITMAPCANVAS_H
#define BITMAPCANVAS_H

#include <QWidget>
#include <QImage>

#define MAX_ROWS    100
#define MAX_COLS    200

class BitmapCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit BitmapCanvas(QWidget *parent = 0);

    void setSize(int cols, int rows);
    int getCols();
    int getRows();

    int getPixel(int col, int row);
    void setPixel(int col, int row, int value);
    void clear();

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);

signals:

public slots:

private:
    int mCols;
    int mRows;

    QImage mBitmap;
};

#endif // BITMAPCANVAS_H
