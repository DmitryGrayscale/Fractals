#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::fracFunc_p MainWindow::fracFunctionsList[FCOUNT] = { &MainWindow::fracCantor,
                                                                 &MainWindow::fracSerpinskiTriangle,
                                                                 &MainWindow::fracDragon,
                                                                 &MainWindow::ffracIFS,
                                                                 &MainWindow::fracKoh,
                                                                 &MainWindow::fracLevy,
                                                                 &MainWindow::randSerpinski,
                                                                 &MainWindow::fracMandelbrot };

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    wgt = NULL;

    ui->setupUi(this);
    connect(ui->fractalsList,SIGNAL(doubleClicked(QModelIndex)),SLOT(on_drawButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fracCantor()
{
    wgt = new FracCantor(ui->scrollArea);
    ui->scrollArea->setWidget(wgt);
}

void MainWindow::fracSerpinskiTriangle()
{
    wgt = new SerpinskiTriangle(ui->scrollArea);
    ui->scrollArea->setWidget(wgt);
}

void MainWindow::fracKoh()
{
    wgt = new FracKoh(ui->scrollArea);
    FracKoh *koh_p = static_cast<FracKoh*>(wgt);
    ui->horizontalLayout->insertWidget(0, koh_p->text);
    ui->horizontalLayout->insertWidget(1, koh_p->sbox);
    ui->scrollArea->setWidget(wgt);
}

void MainWindow::fracLevy()
{
    wgt = new FracLevy(ui->scrollArea);
    FracLevy *levy_p = static_cast<FracLevy*>(wgt);
    ui->horizontalLayout->insertWidget(0, levy_p->text);
    ui->horizontalLayout->insertWidget(1, levy_p->sbox);
    ui->scrollArea->setWidget(wgt);
}

void MainWindow::randSerpinski()
{
    wgt = new RandSerpinski(ui->scrollArea);
    RandSerpinski *serpinski_p = static_cast<RandSerpinski*>(wgt);
    ui->horizontalLayout->insertWidget(0, serpinski_p->sbox);
    ui->horizontalLayout->insertWidget(1, serpinski_p->button);
    ui->scrollArea->setWidget(wgt);
}

void MainWindow::fracMandelbrot()
{
    wgt = new FracMandelbrot(ui->scrollArea);
    FracMandelbrot *m_p = static_cast<FracMandelbrot*>(wgt);
    ui->horizontalLayout->insertWidget(0, m_p->min);
    ui->horizontalLayout->insertWidget(1, m_p->slider);
    ui->horizontalLayout->insertWidget(2, m_p->max);
    ui->horizontalLayout->insertWidget(3, m_p->button);
    ui->scrollArea->setWidget(wgt);
}

void MainWindow::ffracIFS()
{
    wgt = new fracIFS(ui->scrollArea);
    fracIFS *ifs_p = static_cast<fracIFS*>(wgt);
    ui->horizontalLayout->insertWidget(0, ifs_p->text);
    ui->horizontalLayout->insertWidget(1, ifs_p->sbox);
    ui->scrollArea->setWidget(wgt);
}

void MainWindow::fracDragon()
{
    wgt = new FracDragon(ui->scrollArea);
    FracDragon *dragon_p = static_cast<FracDragon*>(wgt);
    ui->horizontalLayout->insertWidget(0, dragon_p->zoomOut);
    ui->horizontalLayout->insertWidget(1, dragon_p->zoomOrig);
    ui->horizontalLayout->insertWidget(2, dragon_p->zoomIn);
    ui->scrollArea->setWidget(wgt);
}

void MainWindow::on_drawButton_clicked()
{
    if (NULL != wgt)
        delete wgt;
    int row = ui->fractalsList->currentRow();
    fracFunc_p fp = (fracFunctionsList[row]);
    if (NULL != fp)
        (this->*fp)();
    if(!isMaximized())
    {
        adjustSize();
        resize(minimumWidth()+500, minimumHeight()+200);
    }
}
