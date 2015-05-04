#ifndef FRACIFS_H
#define FRACIFS_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

namespace Ui {
class fracIFS;
}

class fracIFS : public QWidget
{
    Q_OBJECT

public:
    explicit fracIFS(QWidget *parent = 0);
    ~fracIFS();

    QLabel *text;
    QSpinBox *sbox;
    QPushButton *repaintButton;

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void repaintFractal();
private:
    Ui::fracIFS *ui;
    QPainter *painter;

    qreal xmin;
    qreal xmax;
    qreal ymin;
    qreal ymax;

    int depth;

    void toScreen(QPointF w, QPoint &s);
    void toWorld(QPoint s, QPointF &w);
};

#endif // FRACIFS_H
