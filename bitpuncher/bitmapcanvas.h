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

signals:

public slots:

private:
    int mCols;
    int mRows;

    QImage mBitmap;
};

#endif // BITMAPCANVAS_H
