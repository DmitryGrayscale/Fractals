#include "fracmandelbrot.h"
#include "ui_fracmandelbrot.h"
#include <QDebug>

FracMandelbrot::FracMandelbrot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FracMandelbrot)
{
    slider = new QSlider(Qt::Horizontal, this);
    slider->setMaximumWidth(150);
    slider->setRange(1, 100);
    slider->setValue(85);
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(changeScale(int)));

    min = new QLabel("0", this);
    max = new QLabel("100", this);
    button = new QPushButton("Перерисовать",this);
    connect(button,SIGNAL(clicked()),this,SLOT(repaint()));
    scale = 280;
    xFactor = 2.0;
    yFactor = 2.0;

    ui->setupUi(this);
}

FracMandelbrot::~FracMandelbrot()
{
    delete slider;
    delete min;
    delete max;
    delete ui;
}

void FracMandelbrot::paintEvent(QPaintEvent *event)
{
    (void)event;
    painter = new QPainter(this);
    painter->fillRect(0, 0, width(), height(), QBrush(Qt::black));
    painter->setPen(Qt::white);

    draw();
}

void FracMandelbrot::changeScale(int value)
{
    scale = 3.30 * value;
}

void FracMandelbrot::draw()
{
    for (int y = 0; y < height(); y++)
        for (int x = 0; x < width(); x++)
        {
            double xx = 1.0 * (x - width()/xFactor) / scale;
            double yy = 1.0 * (y - height()/yFactor) / scale;
            double p = qSqrt(((double)xx - 0.25)*((double)xx - 0.25) + yy*yy);
            double angle = qAtan2(yy,xx - 0.25);
            double pc = 0.5 - 0.5*qCos(angle);

            if (p <= pc)
            {
                continue;
            }
            Complex z(0, 0);
            int i = 0;
            while (i < 1000 && Complex::squareAbs(z) < 4)
            {
                z = Complex::sqr(z) + Complex(xx, yy);
                i++;
            }
            if (Complex::squareAbs(z) >= 4)
            {
                int color = 0.255 * (1000-i);

                painter->setPen(QColor(color-color/i, color-color/i, color));
                painter->drawPoint(x,y);
            }
        }
}
