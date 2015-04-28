#ifndef FRACCANTOR_H
#define FRACCANTOR_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class FracCantor;
}

class FracCantor : public QWidget
{
    Q_OBJECT

public:
    explicit FracCantor(QWidget *parent = 0);
    QSize sizeHint() const;
    QSize minimumSizeHint();
    ~FracCantor();
protected:
    void paintEvent(QPaintEvent *event);

private:
    QPainter *painter;
    bool endOfDrawing;
    Ui::FracCantor *ui;

    void drawTT(int left, int right, int top);
};

#endif // FRACCANTOR_H
