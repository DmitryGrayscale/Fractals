#include "fracifs.h"
#include "ui_fracifs.h"
#include <QImage>

fracIFS::fracIFS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fracIFS)
{
    xmin = 1.0;
    xmax = 0.0;
    ymin = 1.0;
    ymax = 0.0;

    depth = 5;
    image = NULL;

    text = new QLabel("Глубина: ", this);
    sbox = new QSpinBox(this);
    sbox->setRange(1,15);
    sbox->setValue(depth);

    connect(sbox, SIGNAL(valueChanged(int)), SLOT(repaintFractal()));

    ui->setupUi(this);
}

fracIFS::~fracIFS()
{
    delete text;
    delete sbox;
    delete ui;
}

QSize fracIFS::sizeHint() const
{
    return QSize(800, 600);
}

QSize fracIFS::minimumSizeHint()
{
    return QSize(800, 600);
}

void fracIFS::paintEvent(QPaintEvent *event)
{
    (void)event;

    const int h = 600;

    if(NULL != image)
    {
        painter = new QPainter(this);
        painter->drawImage(30, 0, *image);
        painter->end();
        return;
    }
    image = new QImage(h, h, QImage::Format_RGB32);
    image->fill(QColor(222,222,222));

    painter = new QPainter(image);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::green);


    qreal C[3][6] = {{0.5,  0,  0,  0.5,     0,    0},
                     {0.5,  0,  0,  0.5,   0.5,    0},
                     {0.5,  0,  0,  0.5,  0.25,  0.43}};


    int E[h][h];
    int S[h][h];

    for (int i = 0; i < h; i++) for (int j = 0; j < h; j++) E[i][j]=1;
    for (int i = 0; i < h; i++) for (int j = 0; j < h; j++) S[i][j]=0;

    for (int mm = 0; mm < depth; mm++)
    {
        for (int i = 0; i < h; i++)
            for (int j = 0; j < h; j++)
                if (E[i][j] == 1)
                {
                    for (int L = 0; L < 3; L++)
                    {
                        QPoint s; QPointF w;

                        s.setX(i); s.setY(j);
                        toWorld(s, w);

                        qreal x = C[L][0] * w.x() + C[L][1] * w.y() + C[L][4];
                        qreal y = C[L][2] * w.x() + C[L][3] * w.y() + C[L][5];

                        w.setX(x); w.setY(y);
                        toScreen(w, s);

                        if ((s.x() >= 0) && (s.x() < h))
                            if ((s.y() >= 0) && (s.y() < h))
                            {
                                S[s.x()][s.y()] = 1;
                                if (mm == depth-1)
                                    painter->drawPoint(s);
                            }
                    }
                }
        for (int i=0;i<h;i++)
            for (int j=0;j<h;j++)
            {
                E[i][j] = S[i][j];
                S[i][j] = 0;
            }
    }
    painter->end();
    painter->begin(this);
    painter->drawImage(30, 0, *image);
    painter->end();
}

void fracIFS::toScreen(QPointF w, QPoint &s)
{
    int widthS = 600;
    int heightS = 600;
    s.setX((w.x()-xmin) / (xmax-xmin) * widthS);
    s.setY((ymax - w.y()) / (ymax - ymin) * heightS);
}

void fracIFS::toWorld(QPoint s, QPointF &w)
{
    int widthS = 600;
    int heightS = 600;
    w.setX(s.x() * (xmax - xmin) / widthS + xmin);
    w.setY(ymax - s.y() * (ymax - ymin) / heightS);
}

void fracIFS::repaintFractal()
{
    depth = sbox->value();
    delete image;
    image = NULL;
    repaint();
}
