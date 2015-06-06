#ifndef FRACMANDELBROT_H
#define FRACMANDELBROT_H

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class FracMandelbrot;
}

class FracMandelbrot : public QWidget
{
    Q_OBJECT

public:
    explicit FracMandelbrot(QWidget *parent = 0);
    ~FracMandelbrot();
    QSlider *slider;
    QLabel *min;
    QLabel *max;
    QPushButton *button;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPainter *painter;
    Ui::FracMandelbrot *ui;
    int scale;
    double xFactor;
    double yFactor;
    void draw();
private slots:
    void changeScale(int value);
};


class Complex
{
public:
    double re;
    double im;
    Complex(double _re, double _im): re(_re), im(_im) {}
    Complex operator+(const Complex &v)
    {
        return Complex(re + v.re, im + v.im);
    }
    static Complex sqr(const Complex &v)
    {
        return Complex(v.re * v.re - v.im * v.im, 2 * v.re * v.im);
    }
    static double abs(const Complex &v)
    {
        return qSqrt(v.re * v.re + v.im * v.im);
    }
    static double squareAbs(const Complex &v)
    {
        return v.re * v.re + v.im * v.im;
    }

};


#endif // FRACMANDELBROT_H
