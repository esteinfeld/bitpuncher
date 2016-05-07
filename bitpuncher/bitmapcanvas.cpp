#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <string.h>

#include "bitmapcanvas.h"

#define DEFAULT_COLS        50
#define DEFAULT_ROWS        8
#define GRID_SIZE           20

BitmapCanvas::BitmapCanvas(QWidget *parent) : QWidget(parent),
    mCols(DEFAULT_COLS),
    mRows(DEFAULT_ROWS)
{
    clear();
    setSize(DEFAULT_COLS, DEFAULT_ROWS);
}

void BitmapCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, size().width() - 1, size().height() - 1);

    for (int row=0 ; row < mRows ; ++row) {
        for (int col=0 ; col < mCols ; ++col) {
            if (mBitmap.pixelIndex(col, row)) {
                float x = col * (size().width() / mCols);
                float y = row * (size().height() / mRows);

                painter.fillRect(x + 2, y + 2, GRID_SIZE - 3, GRID_SIZE - 3, Qt::black);
            }
        }
    }

    for (int row=0 ; row < mRows ; ++row) {
        float y = row * (size().height() / mRows);
        painter.drawLine(0, y, size().width() - 1, y);
    }

    for (int col=1 ; col < mCols ; ++col) {
        float x = col * (size().width() / mCols);
        painter.drawLine(x, 0, x, size().height() - 1);
    }

}

void BitmapCanvas::mousePressEvent(QMouseEvent *event)
{
    int row = event->pos().y() / GRID_SIZE;
    int col = event->pos().x() / GRID_SIZE;
    std::cerr << "Mousy row=" << row << " y=" << col << std::endl;

    if (event->button() == Qt::LeftButton) {
        mBitmap.setPixel(col, row, 1);
    } else if (event->button() == Qt::RightButton) {
        mBitmap.setPixel(col, row, 0);
    }
    repaint();
}

void BitmapCanvas::setSize(int cols, int rows)
{
    mCols = cols;
    mRows = rows;

    mBitmap = QImage(cols, rows, QImage::Format_Mono);
    clear();

    setFixedSize(mCols * GRID_SIZE, mRows * GRID_SIZE);

    std::cerr << "Setting grid size to " << mCols << "x" << mRows << std::endl;
}

int BitmapCanvas::getCols()
{
    return mCols;
}

int BitmapCanvas::getRows()
{
    return mRows;
}

int BitmapCanvas::getPixel(int col, int row)
{
    return mBitmap.pixelIndex(col, row);
}

void BitmapCanvas::setPixel(int col, int row, int value)
{
    mBitmap.setPixel(col, row, value);
}

void BitmapCanvas::clear()
{
    mBitmap.fill(0);
}
