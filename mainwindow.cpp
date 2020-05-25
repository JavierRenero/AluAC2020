#include "mainwindow.h"
#include "QMessageBox"
#include "iee754converter.h"
#include "operaciones.h"
#include "ui_mainwindow.h"
#include <regex>
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
  ui->conversionesBUtton->setStyleSheet("background-image:url(:blanco.jpg);");
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
    mensaje.setText("COMPRUEBE LOS DATOS INTRODUCIDOS!");
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
      if(textoA.toFloat() == -textoB.toFloat()){
          resultado = "0";
      } else {
          Suma suma = Suma();
          resultado = suma.realizarSuma(signoA, exponenteA, mantisaA, signoB,
                                        exponenteB, mantisaB);
      }
      this->v.setNum1(textoA);
      this->v.setNum2(textoB);
      this->v.setResul(resultado);
      pase = true;
      ui->resultText->setText(resultado);
    } else if (ui->signoBox->currentText() == "x") {
      if (textoA.toFloat() == 0 || textoB.toFloat() == 0) {
        resultado = "0";
      } else {
        Multiplicacion multiplicacion = Multiplicacion();
        resultado = multiplicacion.realizarMultiplicacion(
            signoA, exponenteA, mantisaA, signoB, exponenteB, mantisaB);
      }

      this->v.setNum1(textoA);
      this->v.setNum2(textoB);
      this->v.setResul(resultado);
      pase = true;
      ui->resultText->setText(resultado);
    } else if (ui->signoBox->currentText() == "÷") {
      if (textoA.toFloat() == 0 && textoB.toFloat() != 0) {
        resultado = "0";
      } else {
        Division div = Division();
        resultado = div.realizarDivision(signoA, exponenteA, mantisaA, signoB,
                                         exponenteB, mantisaB);
      }
      this->v.setNum1(textoA);
      this->v.setNum2(textoB);
      this->v.setResul(resultado);
      pase = true;
      ui->resultText->setText(resultado);
    } else {
      QMessageBox mensaje;
      mensaje.setWindowIcon(QIcon(":/icon1.png"));
      mensaje.setWindowTitle("ERROR");
      mensaje.setIcon(QMessageBox::Critical);
      mensaje.setText("HA DE SELECCIONAR EL SIGNO DE LA OPERACIÓN!");
      mensaje.exec();
    }
  }
}

// Comprueba si el texto introducido es un numero
bool MainWindow::isNumber(string s) {
  regex s_expr("-?[[:digit:]]+(?:E|e)[[:digit:]]+");
  if (regex_match(s, s_expr)) {
    return true;
  } else {
      istringstream iss(s);
      float num;
      iss >> noskipws >> num;
      return iss && iss.eof();
  }
}
void MainWindow::on_conversionesBUtton_clicked() {
  if (pase) {
    this->v.setModal(true);
    this->v.setText();
    this->v.exec();
  } else {
    QMessageBox mensaje;
    mensaje.setWindowIcon(QIcon(":/icon1.png"));
    mensaje.setWindowTitle("ERROR");
    mensaje.setIcon(QMessageBox::Critical);
    mensaje.setText("TIENE QUE HABER HECHO UNA OPERACIÓN!");
    mensaje.exec();
  }
}
