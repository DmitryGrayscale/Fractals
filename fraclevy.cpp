#include "fraclevy.h"
#include "ui_fraclevy.h"

FracLevy::FracLevy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FracLevy)
{
    depth = 10;

    ui->setupUi(this);

    text = new QLabel("Глубина: ", this);
    sbox = new QSpinBox(this);
    sbox->setRange(0, 20);
    sbox->setValue(depth);

    connect(sbox, SIGNAL(valueChanged(int)), SLOT(repaintFractal()));

}

FracLevy::~FracLevy()
{
    delete text;
    delete sbox;
    delete ui;
}

void FracLevy::paintEvent(QPaintEvent *)
{
    QPointF first(200,400);
    QPointF last(500,400);

    painter = new QPainter(this);
    painter->setPen(Qt::magenta);
    drawLevy(first, last, depth);
}

void FracLevy::drawLevy(QPointF &p1, QPointF &p2, int iter)
{
    if (iter == 0)
    {
        painter->drawLine(p1,p2);
    }
    else
    {
        QPointF p;
        p.setX((p1.x() + p2.x())/2 + (p2.y() - p1.y())/2);
        p.setY((p1.y() + p2.y())/2 - (p2.x() - p1.x())/2);
        drawLevy(p,p2,iter-1);
        drawLevy(p1,p,iter-1);
    }
}

void FracLevy::repaintFractal()
{
    depth = sbox->value();
    repaint();
}
