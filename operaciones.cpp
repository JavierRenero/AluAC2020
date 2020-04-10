#include "operaciones.h"
#include <QDebug>

int * Operaciones::complemento2(int binario[], int &numeroDecimal) {
    numeroDecimal = ~numeroDecimal + 1;
    for(int i = 0; i < 24; i++) {
        if(binario[i]  == 0) {
            binario[i] = 1;
        } else {
            binario[i] = 0;
        }
    }
    int * doses = binario;
    for(int i  = 23; i >=0; i--) {
        if(binario[i] == 1) {
            doses[i] = 0;
        } else {
            doses[i] = 1;
            break;
        }
    }
    return doses;
}

int * Operaciones::conversorBinario(int decimal) {
    int * binario = new int[24];
    int contador = 23;
    for(int i = 0; i<24; i++){
        binario[i] = 0;
    }
    if (decimal > 0) {
        while(decimal >= 1){
            if(decimal % 2 != 0) {
                binario[contador] = 1;
            }
            decimal = decimal/2;
            contador--;
        }
    }
    binario[0] = 1;
    return binario;
}

int * Operaciones:: desplazarBits(int binario[], bool ceros, int desplazamientos) {
    int contador = 0;
    int sustituto = 1;
    if(ceros) sustituto=0;
    while(contador < desplazamientos) {
        for(int i = 24; i > 0; i--) {
            binario[i] = binario[i-1];
        }
        contador++;
        binario[0] = sustituto;
    }
    return binario;
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

    //PASO 4 Y PASO 5
    int  * mantisaBBinaria = new int[23];
    mantisaBBinaria = conversorBinario(mantisaB);
    if(exponenteA != exponenteB) {
        mantisaBBinaria = complemento2(mantisaBBinaria, mantisaB);
    }

    //PASO 6
    if(22 - diferencia + 1 < 23) {
        g = mantisaBBinaria[22 - diferencia + 1];
    }
    if(22 - diferencia + 2 < 23) {
        r = mantisaBBinaria[22 - diferencia + 2];
    }
    int n = 3;
    while(22 - diferencia + n < 23) {
        if(mantisaBBinaria[22 - diferencia + n] == 1){
            st = 1;
        }
    }

    //PASO 7
    if (signoA != signoB) {
        mantisaBBinaria = desplazarBits(mantisaBBinaria, false, diferencia);
    } else {
        mantisaBBinaria = desplazarBits(mantisaBBinaria, true, diferencia);
    }

    for(int i = 0; i<24; i++){
        printf("%d", mantisaBBinaria[i]);
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
