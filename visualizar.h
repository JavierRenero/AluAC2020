#ifndef VISUALIZAR_H
#define VISUALIZAR_H

#include "ui_visualizar.h"
#include <QDialog>

namespace Ui {
class visualizar;
}

class visualizar : public QDialog
{
  Q_OBJECT

public:
  explicit visualizar(QWidget *parent = nullptr);
  ~visualizar();
  Ui::visualizar *getUI();
  void setNum1(QString num1);
  void setNum2(QString num1);
  void setResul(QString num1);
  void setText();
  int *conversorBinario(int decimal, int tam);
  QString conversorHexadecimal(int binario[]);
private:
  Ui::visualizar *ui;
  QString num1;
  QString num2;
  QString result;
};

#endif // VISUALIZAR_H
