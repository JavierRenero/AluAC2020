#ifndef OPERACIONES_H
#define OPERACIONES_H
#include <vector>

using namespace std;

class Operaciones
{
public:
    int * complemento2(int binario[], int &numeroDecimal);
    int * conversorBinario(int decimal);
    int * desplazarBits(int binario[], bool ceros, int desplazamientos);
};

class Suma : Operaciones
{
public:
    Suma();
    int realizarOperaciones(int signoA, int exponenteA, int mantisaA, int signoB, int exponenteB, int mantisaB);
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
