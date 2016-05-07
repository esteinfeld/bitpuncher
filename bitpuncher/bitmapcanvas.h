#ifndef BITMAPCANVAS_H
#define BITMAPCANVAS_H

#include <QWidget>

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

    bool getPixel(int col, int row);
    void setPixel(int col, int row, bool value);
    void clear();

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);

signals:

public slots:

private:
    int mCols;
    int mRows;

    bool mBitmap[MAX_COLS][MAX_ROWS];
};

#endif // BITMAPCANVAS_H
