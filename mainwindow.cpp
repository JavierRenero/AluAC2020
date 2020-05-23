#include "mainwindow.h"
#include "QMessageBox"
#include "iee754converter.h"
#include "operaciones.h"
#include "ui_mainwindow.h"
#include <sstream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("ALU: CALCULADORA");
  this->setWindowIcon(QIcon(":/icon1.png"));
  this->setMinimumSize(725, 253);
  this->setMaximumSize(725, 253);
  ui->signoBox->setStyleSheet("background-image:url(:blanco.jpg);");
  ui->signoBox->setCurrentIndex(-1);
  ui->signoBox->lineEdit()->setAlignment(Qt::AlignCenter);
  ui->signoBox->lineEdit()->setReadOnly(true);
  ui->numberOneText->setAlignment(Qt::AlignCenter);
  ui->numberTwoText->setAlignment(Qt::AlignCenter);
  ui->resultText->setAlignment(Qt::AlignCenter);
  ui->numberOneText->setStyleSheet("background-image:url(:blanco.jpg);");
  ui->numberTwoText->setStyleSheet("background-image:url(:blanco.jpg);");
  ui->resultText->setStyleSheet("background-image:url(:blanco.jpg);");
  ui->calcularButton->setStyleSheet("background-image:url(:blanco.jpg);");
  this->setStyleSheet("background-image:url(:fondo.jpg);");
}
MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_calcularButton_clicked() {
  QString textoA = ui->numberOneText->text();
  QString textoB = ui->numberTwoText->text();
  if (isNumber(textoA.toStdString()) == false ||
      isNumber(textoB.toStdString()) == false) {
    ui->numberOneText->clear();
    ui->numberTwoText->clear();
    ui->signoBox->setCurrentIndex(-1);

    QMessageBox mensaje;
    mensaje.setWindowIcon(QIcon(":/icon1.png"));
    mensaje.setWindowTitle("WARNING");
    mensaje.setIcon(QMessageBox::Warning);
    mensaje.setText("COMPRUEBE LOS DATOS INTRODUCIDOS\n\t  ERROR!");
    mensaje.exec();
  } else {
    floatToIEE ieeConverterA = floatToIEE(textoA.toFloat());
    floatToIEE ieeConverterB = floatToIEE(textoB.toFloat());
    int signoA = ieeConverterA.getSigno();
    int exponenteA = ieeConverterA.getExponente();
    int mantisaA = ieeConverterA.getFraccionaria();
    int signoB = ieeConverterB.getSigno();
    int exponenteB = ieeConverterB.getExponente();
    int mantisaB = ieeConverterB.getFraccionaria();
    QString resultado;
    if (ui->signoBox->currentText() == "+") {
      Suma suma = Suma();
      resultado = suma.realizarSuma(signoA, exponenteA, mantisaA, signoB,
                                    exponenteB, mantisaB);
      ui->resultText->setText(resultado);
    } else if (ui->signoBox->currentText() == "x") {
      Multiplicacion multiplicacion = Multiplicacion();
      resultado = multiplicacion.comaFlotante(signoA, exponenteA, mantisaA,
                                              signoB, exponenteB, mantisaB);
      ui->resultText->setText(resultado);
    } else if (ui->signoBox->currentText() == "÷") {
      Division div = Division();
      resultado = div.divisionCompaFlotante(signoA, exponenteA, mantisaA,
                                            signoB, exponenteB, mantisaB);
      ui->resultText->setText(resultado);
    } else {
      QMessageBox mensaje;
      mensaje.setWindowIcon(QIcon(":/icon1.png"));
      mensaje.setWindowTitle("WARNING");
      mensaje.setIcon(QMessageBox::Warning);
      mensaje.setText("HA DE SELECCIONAR EL SIGNO DE LA OPERACIÓN\t  ERROR!");
      mensaje.exec();
    }
  }
}
bool MainWindow::isNumber(string myString) {
  istringstream iss(myString);
  float f;
  iss >> noskipws >> f;
  return iss.eof() && !iss.fail();
}
