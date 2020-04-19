#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iee754converter.h"
#include "operaciones.h"

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
    QString textoA = ui->numberOneText->text();
    QString textoB = ui->numberTwoText->text();
    floatToIEE ieeConverterA = floatToIEE(textoA.toFloat());
    floatToIEE ieeConverterB = floatToIEE(textoB.toFloat());
    int signoA = ieeConverterA.getSigno();
    int exponenteA = ieeConverterA.getExponente();
    int mantisaA = ieeConverterA.getFraccionaria();
    int signoB = ieeConverterB.getSigno();
    int exponenteB = ieeConverterB.getExponente();
    int mantisaB = ieeConverterB.getFraccionaria();
    float resultado;
    if(ui->sumaButton->isChecked()) {
        Suma suma = Suma();
        resultado = suma.realizarOperaciones(signoA, exponenteA, mantisaA, signoB, exponenteB, mantisaB);
        ui->resultText->setText(QString::number(resultado));
    }
}


