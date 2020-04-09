#include "operaciones.h"
#include <QDebug>

int Operaciones::complemento2(int numero) {
    return ~numero + 1;
}

Suma::Suma()
{
    // PASO 1
    this->g = 0;
    this->r = 0;
    this->st = 0;
    this->operandosIntercambiados = false;
    this->complemento_P = false;
}

int Suma::realizarOperaciones(int signoA, int exponenteA, int mantisaA, int signoB, int exponenteB, int mantisaB){
    //PASO 2
    if(exponenteA < exponenteB) {
           int signoAAux = signoA;
           int exponenteAAux = exponenteA;
           int mantisaAAux = mantisaA;
           signoA = signoB;
           exponenteA = exponenteB;
           mantisaA = mantisaB;
           signoB = signoAAux;
           exponenteB = exponenteAAux;
           mantisaB = mantisaAAux;
           operandosIntercambiados = true;
    }

    //PASO 3
    int exponenteSuma = exponenteA;
    int diferencia = exponenteA - exponenteB;

    //PASO 4
    if(exponenteA != exponenteB) {
        mantisaB = complemento2(mantisaB); // CREO QUE ESTA BIEN SI ALGO SALE MAS AL FINAL REVISAR
    }

    //PASO 5
    int P = mantisaB;

    //PASO 6
    //RELLENAR

    //PASO 7
    if (signoA != signoB) {
        // RELLENAR
    } else {
        // RELLENAR
    }

    //PASO 8
    // RELLENAR

    //PASO 9
    // RELLENAR

    //PASO 10
    // RELLENAR

    //PASO 11
    // RELLENAR

    //PASO 12
    // RELLENAR

    //PASO 13
    // RELLENAR
    return 0;
}
