#ifndef RANDSERPINSKI_H
#define RANDSERPINSKI_H

#include <QWidget>
#include <QPainter>
#include <QSpinBox>
#include <QPushButton>

namespace Ui {
class RandSerpinski;
}

class RandSerpinski : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event);

public:
    explicit RandSerpinski(QWidget *parent = 0);
    ~RandSerpinski();

    QPushButton *button;
    QSpinBox *sbox;
private slots:
    void repaintFractal();
private:
    int depth;
    QPainter *painter;
    Ui::RandSerpinski *ui;
};

#endif // RANDSERPINSKI_H
