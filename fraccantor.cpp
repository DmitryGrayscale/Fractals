#include "fraccantor.h"
#include "ui_fraccantor.h"

FracCantor::FracCantor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FracCantor)
{
    endOfDrawing = false;
    ui->setupUi(this);
}

FracCantor::~FracCantor()
{
    delete ui;
}

QSize FracCantor::sizeHint() const
{
    return QSize(650,500);
}

QSize FracCantor::minimumSizeHint()
{
    return QSize(650,500);
}

void FracCantor::paintEvent(QPaintEvent *event)
{
    (void)event;
    painter = new QPainter(this);
    painter->setPen(Qt::blue);
//    painter->setRenderHint(QPainter::Antialiasing, true);
    drawTT(10, 610, 50);
    painter->end();
}

void FracCantor::drawTT(int left, int right, int top)
{
    if (top > 300)
    {
        return;
    }

    int lmiddle = left + (right - left)/6;
    int rmiddle = right - (right - left)/6;
    int bottom = top + 50;

    painter->drawLine(QPointF(left, top), QPointF(right, top));
    painter->drawLine(QPointF(lmiddle, top), QPointF(lmiddle, bottom));
    painter->drawLine(QPointF(rmiddle, top), QPointF(rmiddle, bottom));

    drawTT(left, left + (right - left)/3, bottom);
    drawTT(right - (right - left)/3, right, bottom);
}
