#ifndef FRACLEVY_H
#define FRACLEVY_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

namespace Ui {
class FracLevy;
}

class FracLevy : public QWidget
{
    Q_OBJECT

public:
    explicit FracLevy(QWidget *parent = 0);
    ~FracLevy();

    QLabel *text;
    QSpinBox *sbox;

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void repaintFractal();
private:
    int depth;
    Ui::FracLevy *ui;
    QPainter *painter;
    void drawLevy(QPointF &p1, QPointF &p2, int iter);
};

#endif // FRACLEVY_H
