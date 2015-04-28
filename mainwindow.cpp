#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::fracFunc_p MainWindow::fracFunctionsList[FCOUNT] = { &MainWindow::fracCantor,
                                                                 &MainWindow::fracSerpinskiTriangle,
                                                                 &MainWindow::fracDragon,
                                                                 NULL,
                                                                 NULL};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
    delete wgt;
    int row = ui->fractalsList->currentRow();
    fracFunc_p fp = (fracFunctionsList[row]);
    if (NULL != fp)
        (this->*fp)();
    adjustSize();
    resize(minimumWidth()+500, minimumHeight()+200);
}
