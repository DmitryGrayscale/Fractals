#ifndef SERPINSKITRIANGLE_H
#define SERPINSKITRIANGLE_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

namespace Ui {
class SerpinskiTriangle;
}

class SerpinskiTriangle : public QWidget
{
    Q_OBJECT

public:
    explicit SerpinskiTriangle(QWidget *parent = 0);
    QSize sizeHint() const;
    QSize minimumSizeHint();
    ~SerpinskiTriangle();
protected:
    void paintEvent(QPaintEvent *event);

private:
    QPainter *painter;
    Ui::SerpinskiTriangle *ui;
    QPointF T3(QPointF point, qreal rx, qreal yc);
    QPointF T2(QPointF point, qreal xc);
    QPointF T1(QPointF point);
    void drawBase(QPainterPath *path, QPainterPath *pathpp);
    void drawMain(QPointF *points, quint32 depth);
};

#endif // SERPINSKITRIANGLE_H
