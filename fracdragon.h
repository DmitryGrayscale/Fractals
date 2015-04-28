#ifndef FRACDRAGON_H
#define FRACDRAGON_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>

namespace Ui {
class FracDragon;
}

class FracDragon : public QWidget
{
    Q_OBJECT

public:
    explicit FracDragon(QWidget *parent = 0);
    ~FracDragon();

    QPushButton *zoomIn;
    QPushButton *zoomOut;
    QPushButton *zoomOrig;

    QSize sizeHint() const;
    QSize minimumSizeHint();

protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::FracDragon *ui;
    QPainter *painter;
    qreal scaleFactor;
    int hintWidth;
    int hintHeight;

    int getDirection(int i);
private slots:
    void setZoomIn();
    void setZoomOut();
    void setZoomOrig();

};

#endif // FRACDRAGON_H
