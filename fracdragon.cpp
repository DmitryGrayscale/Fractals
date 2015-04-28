#include "fracdragon.h"
#include "ui_fracdragon.h"
#include <QtMath>
#include <QDebug>
#include <QScrollArea>

FracDragon::FracDragon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FracDragon)
{
    zoomIn   = new QPushButton(QIcon::fromTheme("zoom-in"),"", this);
    zoomOut  = new QPushButton(QIcon::fromTheme("zoom-out"),"", this);
    zoomOrig = new QPushButton(QIcon::fromTheme("zoom-original"),"", this);

    scaleFactor = 1;
    hintHeight  = 1000;
    hintWidth   = 1000;

    connect(zoomIn,  SIGNAL(clicked()),SLOT(setZoomIn()));
    connect(zoomOut, SIGNAL(clicked()),SLOT(setZoomOut()));
    connect(zoomOrig,SIGNAL(clicked()),SLOT(setZoomOrig()));

    ui->setupUi(this);
}

FracDragon::~FracDragon()
{
    delete zoomIn;
    delete zoomOut;
    delete zoomOrig;
    delete ui;
}

QSize FracDragon::sizeHint() const
{
    return QSize(hintWidth, hintHeight);
}

QSize FracDragon::minimumSizeHint()
{
    return QSize(500,500);
}

void FracDragon::paintEvent(QPaintEvent *event)
{
    (void)event;

    painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::green);
    painter->setMatrix(QMatrix(1.0, 0.0, 0.0, -1.0, this->width()/2, this->height()/2));
    painter->scale(scaleFactor, scaleFactor);

    QPointF left(300,200);

    qreal angle = M_PI/2;
    int d = 3;
    for (int i = 1; i < 1024*36; i++)
    {
        QPointF right(left.x() + d*qCos(angle), left.y() - d*qSin(angle));

        painter->drawLine(left, right);
        left.setX(left.x() + d*qCos(angle));
        left.setY(left.y() - d*qSin(angle));
        angle = angle - M_PI/2 * getDirection(i);
    }
    painter->end();
}


int FracDragon::getDirection(int i)
{
    if (i % 4 == 1) return 1;
    else if (i % 4 == 3) return -1;
    else getDirection(i/2);
}

void FracDragon::setZoomIn()
{
    if (!zoomOut->isEnabled())
        zoomOut->setEnabled(true);

    if (scaleFactor < 1)
    {
        scaleFactor+=0.25;
        hintHeight = 1000 * scaleFactor;
        hintWidth  = 1000 * scaleFactor;
        update();
        updateGeometry();
    }
    else if (scaleFactor < 5)
    {
        scaleFactor++;
        hintHeight = 1000 * scaleFactor;
        hintWidth  = 1000 * scaleFactor;
        update();
        updateGeometry();
    }
    if (scaleFactor == 5)
        zoomIn->setDisabled(true);
}

void FracDragon::setZoomOut()
{
    if (!zoomIn->isEnabled())
        zoomIn->setEnabled(true);
    if (scaleFactor > 1)
    {
        scaleFactor--;
        hintHeight = 1000 * scaleFactor;
        hintWidth  = 1000 * scaleFactor;
        update();
        updateGeometry();
    }
    else if (scaleFactor <= 1)
    {
        scaleFactor-=0.25;
        hintHeight = 1000 * scaleFactor;
        hintWidth  = 1000 * scaleFactor;
        update();
        updateGeometry();
    }
    if (scaleFactor == 0.25)
    {
        zoomOut->setDisabled(true);
    }
}

void FracDragon::setZoomOrig()
{
    if (!zoomIn->isEnabled())
        zoomIn->setEnabled(true);
    if (!zoomOut->isEnabled())
        zoomOut->setEnabled(true);

    scaleFactor = 1;
    hintHeight  = 1000;
    hintWidth   = 1000;
    update();
    updateGeometry();
}
