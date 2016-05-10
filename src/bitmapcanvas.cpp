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
    mbMouseDragging = true;
    mouseMoveEvent(event);
}

void BitmapCanvas::mouseMoveEvent(QMouseEvent *event)
{
    int col = event->pos().x() / GRID_SIZE;
    int row = event->pos().y() / GRID_SIZE;

    if (col >= mBitmap.size().width() || row >= mBitmap.size().height() ||
            col < 0 || row < 0) {
        return;
    }

    if ((event->buttons() & Qt::LeftButton) && mBitmap.pixelIndex(col, row) == 0) {
        mBitmap.setPixel(col, row, 1);
        repaint();
    } else if ((event->buttons() & Qt::RightButton) && mBitmap.pixelIndex(col, row) == 1) {
        mBitmap.setPixel(col, row, 0);
        repaint();
    }
}

void BitmapCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    mbMouseDragging = false;
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

const QImage& BitmapCanvas::getBitmap()
{
    return mBitmap;
}

void BitmapCanvas::setBitmap(const QImage& bitmap)
{
    mBitmap = QImage(bitmap);
}

void BitmapCanvas::clear()
{
    mBitmap.fill(0);
}
