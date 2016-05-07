#ifndef BITMAPCANVAS_H
#define BITMAPCANVAS_H

#include <QFrame>

class BitmapCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit BitmapCanvas(QWidget *parent = 0);

    void setSize(int cols, int rows);

protected:
    virtual void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    int mCols;
    int mRows;
};

#endif // BITMAPCANVAS_H
