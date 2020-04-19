#ifndef OPERACIONES_H
#define OPERACIONES_H
#include <vector>

using namespace std;

class Operaciones
{
public:
    int * complemento2(int binario[], int &numeroDecimal);
    int * conversorBinario(int decimal);
    int * desplazarBitsDerecha(int binario[], bool ceros, int desplazamientos);
    int * desplazarBitsIzquierda(int binario[], bool ceros, int desplazamientos);
    int * sumaBinario(int binario1[], int binario2[], int &acarreo);
    int  mantisaNormalizada(int binario[]);
    int conversorDecimal(int binario[]);
};

class Suma : Operaciones
{
public:
    Suma();
    float realizarOperaciones(int signoA, int exponenteA, int mantisaA, int signoB, int exponenteB, int mantisaB);
private:
    int g, r, st, n;
    bool operandosIntercambiados, complemento_P;
};

class Multiplicacion : Operaciones
{

};

class Division : Operaciones
{

};

#endif // OPERACIONES_H
