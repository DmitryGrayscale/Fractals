#include "randserpinski.h"
#include "ui_randserpinski.h"
#include <QtGlobal>

RandSerpinski::RandSerpinski(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RandSerpinski)
{
    depth = 10000;

    ui->setupUi(this);

    button = new QPushButton("Go!", this);
    sbox = new QSpinBox(this);
    sbox->setRange(0, depth*100);
    sbox->setValue(depth);

    connect(button, SIGNAL(clicked()), SLOT(repaintFractal()));
}

RandSerpinski::~RandSerpinski()
{
    delete sbox;
    delete button;
    delete ui;
}

void RandSerpinski::repaintFractal()
{
    depth = sbox->value();
    repaint();
}

void RandSerpinski::paintEvent(QPaintEvent *)
{
    float C[3][6] = {
    {0.5, 0, 0, 0.5, 0, 0},
    {0.5, 0, 0, 0.5, 0.5, 0},
    {0.5, 0, 0, 0.5, 0.25, 0.43301}
    };


    painter = new QPainter(this);
    painter->setPen(Qt::magenta);


    float xmin = 1.0,xmax = 0,ymin = 1.0,ymax = 0;
    float xscale = (width()) / (xmax - xmin);
    float yscale = (height()) / (ymax - ymin);
    float x0 = 0.1, y0 = 0.1, x=0, y=0;
    qsrand(qrand());
    int i;
    for(int j=0; j < depth; j++)
    {
        i = qrand() % 3;
        x = C[i][0]*x0 + C[i][1]*y0 + C[i][4];
        y = C[i][2]*x0 + C[i][3]*y0 + C[i][5];
        painter->drawPoint(xscale * (x - xmin), yscale * (y - ymin));
        x0 = x;
        y0 = y;
    }
}
