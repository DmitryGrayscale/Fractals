#include "serpinskitriangle.h"
#include "ui_serpinskitriangle.h"

SerpinskiTriangle::SerpinskiTriangle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerpinskiTriangle)
{
    ui->setupUi(this);
}

QSize SerpinskiTriangle::sizeHint() const
{
    return QSize(600,500);
}

QSize SerpinskiTriangle::minimumSizeHint()
{
    return QSize(500,500);
}

SerpinskiTriangle::~SerpinskiTriangle()
{
    delete ui;
}

void SerpinskiTriangle::paintEvent(QPaintEvent *event)
{
    (void)event;
    painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);

    QPointF points[3] =
    {
        QPointF(300, 500),
        QPointF(0, 0),
        QPointF(600, 0)
    };

    drawMain(points, 6);
    painter->end();
}

void SerpinskiTriangle::drawBase(QPainterPath *path, QPainterPath *pathpp)
{
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawPath(*path);

    painter->setPen(Qt::blue);
    painter->setBrush(Qt::blue);
    painter->drawPath(*pathpp);
}

void SerpinskiTriangle::drawMain(QPointF *points, quint32 depth)
{
    QPainterPath *path = new QPainterPath();
    QPainterPath *pathpp = new QPainterPath();

    qreal halfWidth = (points[2].x() - points[1].x()) * 0.5;
    qreal quarterWidth = (points[2].x() - points[1].x()) * 0.25;
    qreal halfHeight = (points[0].y() - points[1].y()) * 0.5;

    QPointF p1[3] =
    {
        T1(points[0]),
        T1(points[1]),
        T1(points[2])
    };
    QPointF p2[3] =
    {
        T2(points[0],halfWidth),
        T2(points[1],halfWidth),
        T2(points[2],halfWidth)
    };
    QPointF p3[3] =
    {
        T3(points[0], quarterWidth, halfHeight),
        T3(points[1], quarterWidth, halfHeight),
        T3(points[2], quarterWidth, halfHeight)
    };

    QPolygonF pp1;
    pp1 << p1[0]
        << p1[1]
        << p1[2];
    QPolygonF pp2;
    pp2 << p2[0]
        << p2[1]
        << p2[2];

    QPolygonF pp3;
    pp3 << p3[0]
        << p3[1]
        << p3[2];

    QPolygonF poly;
    poly << points[0] << points[1] << points[2];

    path->addPolygon(poly);
    pathpp->addPolygon(pp1);
    pathpp->addPolygon(pp2);
    pathpp->addPolygon(pp3);

    drawBase(path, pathpp); //white triangle and three small blue triangles

    delete path;
    delete pathpp;

    if (depth > 0)
    {
        drawMain(p1, depth-1);
        painter->save();
        painter->translate(pp2.data()[1]);
        drawMain(p1, depth-1);
        painter->restore();
        painter->save();
        painter->translate(pp3.data()[1]);
        drawMain(p1, depth-1);
        painter->restore();

    }
}

QPointF SerpinskiTriangle::T1(QPointF point)
{
    return QPointF(point.x()*0.5, point.y()*0.5);
}

QPointF SerpinskiTriangle::T2(QPointF point, qreal xc)
{
    return QPointF(point.x()*0.5 + xc, point.y()*0.5);
}

QPointF SerpinskiTriangle::T3(QPointF point, qreal rx, qreal yc)
{
    return QPointF(point.x()*0.5 + rx, point.y()*0.5 + yc);
}
