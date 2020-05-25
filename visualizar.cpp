#include "visualizar.h"
#include "ui_visualizar.h"

visualizar::visualizar(QWidget *parent) :
                                          QDialog(parent),
                                          ui(new Ui::visualizar)
{
  ui->setupUi(this);
}

visualizar::~visualizar()
{
  delete ui;
}
void visualizar::setNum1(QString num1) { this->num1 = num1; }
void visualizar::setNum2(QString num2) { this->num2 = num2; }
void visualizar::setResul(QString resul) { this->result = resul; }

void visualizar::setText() {
  int *num1Bin = new int[32];
  int *num2Bin = new int[32];
  int *resulBin = new int[32];
  num1Bin = conversorBinario(this->num1.toFloat(), 32);
  num2Bin = conversorBinario(this->num2.toFloat(), 32);
  resulBin = conversorBinario(this->result.toFloat(), 32);
  QString num1BinString;
  QString num2BinString;
  QString resulBinString;
  for (int i = 0; i < 32; i++) {
    num1BinString.push_back(num1Bin[i] + '0');
    num2BinString.push_back(num2Bin[i] + '0');
    resulBinString.push_back(resulBin[i] + '0');
  }
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
  binario[0] = 1;
  return binario;
}
