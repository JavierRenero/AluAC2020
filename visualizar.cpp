#include "visualizar.h"
#include "QIcon"
#include "iee754converter.h"
#include "ui_visualizar.h"
#include <math.h>
#include <sstream>

visualizar::visualizar(QWidget *parent)
    : QDialog(parent), ui(new Ui::visualizar) {
  ui->setupUi(this);
  this->setWindowTitle("ALU: CONVERSIONES");
  this->setWindowIcon(QIcon(":/icon1.png"));
  this->setMinimumSize(951, 606);
  this->setMaximumSize(951, 606);
  ui->groupBox->setStyleSheet("background-image:url(:vacio.png);");
  ui->groupBox_2->setStyleSheet("background-image:url(:vacio.png);");
  ui->groupBox_3->setStyleSheet("background-image:url(:vacio.png);");
  ui->num1Hex->setStyleSheet("background-image:url(:blanco.jpg);");
  ui->num2Hex->setStyleSheet("background-image:url(:blanco.jpg);");
  ui->resulHex->setStyleSheet("background-image:url(:blanco.jpg);");
  ui->num1Iee->setStyleSheet("background-image:url(:blanco.jpg);");
  ui->num2Iee->setStyleSheet("background-image:url(:blanco.jpg);");
  ui->resulIee->setStyleSheet("background-image:url(:blanco.jpg);");
  ui->num1Hex->setAlignment(Qt::AlignCenter);
  ui->num2Hex->setAlignment(Qt::AlignCenter);
  ui->resulHex->setAlignment(Qt::AlignCenter);
  ui->num1Iee->setAlignment(Qt::AlignCenter);
  ui->num2Iee->setAlignment(Qt::AlignCenter);
  ui->resulIee->setAlignment(Qt::AlignCenter);
  this->setStyleSheet("background-image:url(:fondo1.jpg);");
}

visualizar::~visualizar() { delete ui; }

Ui::visualizar *visualizar::getUI() { return this->ui; }

void visualizar::setNum1(QString num1) { this->num1 = num1; }
void visualizar::setNum2(QString num2) { this->num2 = num2; }
void visualizar::setResul(QString resul) { this->result = resul; }

void visualizar::setText() {
  int *exp1 = new int[8];
  int *exp2 = new int[8];
  int *expResul = new int[8];

  int *man1 = new int[23];
  int *man2 = new int[23];
  int *manResul = new int[23];

  floatToIEE IEEnum1 = floatToIEE(num1.toFloat());
  floatToIEE IEEnum2 = floatToIEE(num2.toFloat());
  floatToIEE IEEresul = floatToIEE(result.toFloat());

  exp1 = conversorBinario(IEEnum1.getExponente(), 8);
  exp2 = conversorBinario(IEEnum2.getExponente(), 8);
  expResul = conversorBinario(IEEresul.getExponente(), 8);

  man1 = conversorBinario(IEEnum1.getFraccionaria(), 23);
  man2 = conversorBinario(IEEnum2.getFraccionaria(), 23);
  manResul = conversorBinario(IEEresul.getFraccionaria(), 23);

  QString num1BinString = "";
  QString num2BinString = "";
  QString resulBinString = "";

  int *hexaNum1 = new int[4];
  int *hexaNum2 = new int[4];
  int *hexaNumResul = new int[4];

  QString hex1 = "0x";
  QString hex2 = "0x";
  QString hexResul = "0x";

  for (int i = 0; i < 32; i++) {
    if (i > 0 && i % 4 == 0) {
      hex1 += conversorHexadecimal(hexaNum1);
      hex2 += conversorHexadecimal(hexaNum2);
      hexResul += conversorHexadecimal(hexaNumResul);
      for (int i = 0; i < 4; i++) {
        hexaNum1[i] = 0;
        hexaNum2[i] = 0;
        hexaNumResul[i] = 0;
      }
    }
    if (i == 0) {
      num1BinString.push_back(IEEnum1.getSigno() + '0');
      num2BinString.push_back(IEEnum2.getSigno() + '0');
      resulBinString.push_back(IEEresul.getSigno() + '0');
      hexaNum1[0] = IEEnum1.getSigno();
      hexaNum2[0] = IEEnum2.getSigno();
      hexaNumResul[0] = IEEresul.getSigno();
    } else if (i < 9) {
      num1BinString.push_back(exp1[i - 1] + '0');
      num2BinString.push_back(exp2[i - 1] + '0');
      resulBinString.push_back(expResul[i - 1] + '0');
      hexaNum1[i % 4] = exp1[i - 1];
      hexaNum2[i % 4] = exp2[i - 1];
      hexaNumResul[i % 4] = expResul[i - 1];
    } else {
      num1BinString.push_back(man1[i - 9] + '0');
      num2BinString.push_back(man2[i - 9] + '0');
      resulBinString.push_back(manResul[i - 9] + '0');
      hexaNum1[i % 4] = man1[i - 9];
      hexaNum2[i % 4] = man2[i - 9];
      hexaNumResul[i % 4] = manResul[i - 9];
    }
  }
  hex1 += conversorHexadecimal(hexaNum1);
  hex2 += conversorHexadecimal(hexaNum2);
  hexResul += conversorHexadecimal(hexaNumResul);

  this->ui->num1Iee->setText(num1BinString);
  this->ui->num2Iee->setText(num2BinString);
  this->ui->resulIee->setText(resulBinString);

  this->ui->num1Hex->setText(hex1);
  this->ui->num2Hex->setText(hex2);
  this->ui->resulHex->setText(hexResul);
}

int *visualizar::conversorBinario(int decimal, int tam) {
  int *binario = new int[tam];
  int contador = tam - 1;
  for (int i = 0; i < tam; i++) {
    binario[i] = 0;
  }
  if (decimal > 0) {
    while (decimal >= 1) {
      if (decimal % 2 != 0) {
        binario[contador] = 1;
      }
      decimal = decimal / 2;
      contador--;
    }
  }
  return binario;
}

QString visualizar::conversorHexadecimal(int binario[]) {
  int resultado = 0;
  int cont = 3;
  for (int i = 0; i < 4; i++) {
    if (binario[i] == 1) {
      resultado += pow(2, cont);
    }
    cont--;
  }
  switch (resultado) {
  case 10:
    return "A";
    break;
  case 11:
    return "B";
    break;
  case 12:
    return "C";
    break;
  case 13:
    return "D";
    break;
  case 14:
    return "E";
    break;
  case 15:
    return "F";
    break;
  default:
    return QString::number(resultado);
  }
}
