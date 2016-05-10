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

#ifndef BITMAPCANVAS_H
#define BITMAPCANVAS_H

#include <QWidget>
#include <QImage>

class BitmapCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit BitmapCanvas(QWidget *parent = 0);

    void setSize(int cols, int rows);
    int getCols();
    int getRows();

    const QImage& getBitmap();
    void setBitmap(const QImage&);
    void clear();

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:

private:
    int mCols;
    int mRows;

    bool mbMouseDragging;

    QImage mBitmap;
};

#endif // BITMAPCANVAS_H
