#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iee754converter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calcularButton_clicked()
{
    QString texto = ui->numFloatLineEdit->text();
    floatToIEE ieeConverter = floatToIEE(texto.toFloat());
    ui->numIEE754LineEdit->setText(QString::number(ieeConverter.getSigno())+" "+QString::number(ieeConverter.getExponente())+" "+QString::number(ieeConverter.getFraccionaria()));
    IEEToFloat floatConverter = IEEToFloat(ieeConverter.getSigno(), ieeConverter.getExponente(), ieeConverter.getFraccionaria());
    ui->secondFloatLineEdit->setText(QString::number(floatConverter.getNumber()));
}
