#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "visualizar.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calcularButton_clicked();
    bool isNumber(std::string someString);

    void on_conversionesBUtton_clicked();

  private:
    Ui::MainWindow *ui;
    visualizar *v;
    bool pase = false;
};
#endif // MAINWINDOW_H
