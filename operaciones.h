#ifndef OPERACIONES_H
#define OPERACIONES_H
#include <vector>
#include <QString>

using namespace std;

class Operaciones
{
public:
    int * complemento2(int binario[]);
    int * conversorBinario(int decimal, int tam);
    int * desplazarBitsDerecha(int binario[], bool ceros, int desplazamientos);
    int * desplazarBitsIzquierda(int binario[], bool ceros, int desplazamientos);
    int * sumaBinario(int binario1[], int binario2[], int &acarreo);
    int  mantisaNormalizada(int binario[]);
    int conversorEnteros(int binario[]);
    float conversorDecimal(int binario[]);
};

class Suma : Operaciones
{
public:
    Suma();
    QString realizarOperaciones(int signoA, int exponenteA, int mantisaA, int signoB, int exponenteB, int mantisaB);
private:
    int g, r, st, n;
    bool operandosIntercambiados, complemento_P;
};

class Multiplicacion : Operaciones
{
public:
    Multiplicacion();
    QString comaFlotante(int signoA, int exponenteA, int mantisaA, int signoB, int exponenteB, int mantisaB);
private:

};

class MultiplicacionSinSigno : Operaciones
{
public:
    MultiplicacionSinSigno(int mantisaA, int mantisaB);
    int * getP();
    int * getA();
private:
    int * P;
    int * A;
    int * B;
};

class Division : Operaciones
{
public:
    Division();
    QString divisionCompaFlotante(int signoA, int exponenteA, int mantisaA, int signoB, int exponenteB, int mantisaB);
private:

};

#endif // OPERACIONES_H
