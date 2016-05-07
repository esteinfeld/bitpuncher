#include <QPainter>

#include "bitmapcanvas.h"

#define DEFAULT_COLS        50
#define DEFAULT_ROWS        8
#define GRID_SIZE           20

BitmapCanvas::BitmapCanvas(QWidget *parent) : QWidget(parent),
    mCols(DEFAULT_COLS),
    mRows(DEFAULT_ROWS)
{
    setFixedSize(mCols * GRID_SIZE, mRows * GRID_SIZE);
}

void BitmapCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, size().width() - 1, size().height() - 1);

    for (int row=0 ; row < mRows ; ++row) {
        float y = row * (size().height() / mRows);
        painter.drawLine(0, y, size().width() - 1, y);
    }

    for (int col=1 ; col < mCols ; ++col) {
        float x = col * (size().width() / mCols);
        painter.drawLine(x, 0, x, size().height() - 1);
    }
}

void BitmapCanvas::setSize(int cols, int rows)
{
    mCols = cols;
    mRows = rows;

    setFixedSize(mCols * GRID_SIZE, mRows * GRID_SIZE);
}
