#include "operaciones.h"
#include <QDebug>
#include "iee754converter.h"
#include "math.h"
#define MAX_REPRESENTABLE 150
#define EXPONENTE_MINIMO 127
#define TAM_MANTISA 24

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

int * Operaciones::conversorBinario(int decimal, int tam) {
    int * binario = new int[tam];
    int contador = tam-1;
    for(int i = 0; i<tam; i++){
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

int * Operaciones:: desplazarBitsDerecha(int binario[], bool ceros, int desplazamientos) {
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

int * Operaciones:: desplazarBitsIzquierda(int binario[], bool ceros, int desplazamientos) {
    int contador = 0;
    int sustituto = 1;
    if(ceros) sustituto=0;
    while(contador < desplazamientos) {
        for(int i = 0; i < 24; i++) {
            binario[i] = binario[i+1];
        }
        contador++;
        binario[23] = sustituto;
    }
    return binario;
}

int * Operaciones:: sumaBinario(int binario1[], int binario2[], int &acarreo) {
    int * resultado = new int[24];
    for(int i = 23; i >= 0; i--){
        resultado[i] = (binario1[i] + binario2[i] + acarreo) % 2;
        if(binario1[i] + binario2[i] + acarreo > 1)
            acarreo = 1;
        else
            acarreo = 0;
    }
    return resultado;
}

int Operaciones:: mantisaNormalizada(int binario[]) {
    int contador = 0;
    while(contador < 24){
        if(binario[contador] == 1)
            return contador;
        contador++;
    }
    return contador;
}

int Operaciones:: conversorEnteros(int binario[]) {
    int decimal = 0;
    int contador = 0;
    for(int i = 22; i >= 0; i--) {
        if(binario[i] == 1) {
            decimal += pow(2, contador);
        }
        contador++;
    }
    return decimal;
}

float Operaciones:: conversorDecimal(int binario[]) {
    float decimal = 0;
    int contador = -1;
    for(int i = 0; i < 23; i++) {
        if(binario[i] == 1) {
            decimal += pow(2, contador);
        }
        contador--;
    }
    return decimal;
}

Suma::Suma()
{
    // PASO 1
    this->g = 0;
    this->r = 0;
    this->st = 0;
    this->n = 24;
    this->operandosIntercambiados = false;
    this->complemento_P = false;
}

float Suma::realizarOperaciones(int signoA, int exponenteA, int mantisaA, int signoB, int exponenteB, int mantisaB){
    //PASO 2
    if(exponenteA < exponenteB) {
        qDebug() << "Estoy dentro PASO 2";
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
    int d = exponenteA - exponenteB;
    qDebug() << "PASO 3\n" << "Exponente Suma: " << exponenteSuma << "\nDiferencia: " << d;

    //PASO 4 Y PASO 5
    int  * mantisaBBinaria = new int[24];
    // Pasamos la mantisa a binario
    mantisaBBinaria = conversorBinario(mantisaB, 24);
    if(signoA != signoB) {
        mantisaBBinaria = complemento2(mantisaBBinaria, mantisaB);
    }
    mantisaBBinaria[0] = 1;
    qDebug() << "PASO 4 Y 5";
    for(int i = 0; i < 24; i++){
        qDebug() << mantisaBBinaria[i];
    }

    //PASO 6
    if(22 - d + 1 < 23) {
        g = mantisaBBinaria[23 - d + 1];
    }
    if(22 - d + 2 < 23) {
        r = mantisaBBinaria[23 - d + 2];
    }
    int n = 3;
    while(22 - d + n < 23) {
        if(mantisaBBinaria[23 - d + n] == 1){
            st = 1;
        }
        d--;
    }
    qDebug() << "PASO 6\n" << "G: " << g << "\nR: " << r << "ST: " << st;


    //PASO 7
    if (signoA != signoB) {
        mantisaBBinaria = desplazarBitsDerecha(mantisaBBinaria, false, d);
    } else {
        mantisaBBinaria = desplazarBitsDerecha(mantisaBBinaria, true, d);
    }
    qDebug() << "PASO 7";
    for (int i=0; i<24; i++){
        qDebug() << mantisaBBinaria[i];
    }

    //PASO 8
    int * mantisaABinaria = conversorBinario(mantisaA, 24);
    mantisaABinaria[0] = 1;
    int acarreo = 0;
    mantisaBBinaria = sumaBinario(mantisaABinaria, mantisaBBinaria, acarreo);
    qDebug() << "PASO 8";
    for(int i = 0; i<24; i++)
        qDebug() << mantisaBBinaria[i];
    qDebug() << "Acarreo: " << acarreo;

    //PASO 9
    if(signoA != signoB && mantisaBBinaria[0] == 1 && acarreo == 0) {
        mantisaBBinaria = complemento2(mantisaBBinaria, mantisaB);
        complemento_P = true;
    }
    qDebug() << "PASO 9";


    //PASO 10
    if(signoA == signoB && acarreo == 1){
        if(g || r || st == 0){
            st = 0;
        } else {
            st = 1;
        }
        r = mantisaBBinaria[this->n - 1];
        mantisaBBinaria = desplazarBitsDerecha(mantisaBBinaria, false, 1);
        exponenteSuma++;
    } else {
        int k = mantisaNormalizada(mantisaBBinaria);
        if(k == 0){
            if(r || st == 0)
                st = 0;
            else
                st = 1;
        } else {
            r = 0;
            st = 0;
        }
        mantisaBBinaria = desplazarBitsIzquierda(mantisaBBinaria, true, k);
        exponenteSuma -= k;
    }

    //PASO 11
    int c2 = 0;
    if ((r == 1 && st == 1) || (r == 1 && st == 0 && mantisaBBinaria[23] == 1)){
        qDebug() << "HOLA\n";
        // mantisaBBinaria = sumaBinario(mantisaBBinaria, 1, c2);
        if(c2 == 1) {
            mantisaBBinaria = desplazarBitsDerecha(mantisaBBinaria, true, 1);
            exponenteSuma++;
        }
    }

    int * mantisaSumaNormalizada = new int[23];
    for(int i = 22; i >= 0; i--) {
        mantisaSumaNormalizada[i] = mantisaBBinaria[i+1];
    }

    //PASO 12
    int signoSuma;
    if (!operandosIntercambiados && complemento_P){
        signoSuma = signoB;
    } else {
        signoSuma = signoA;
    }

    //PASO 13
    IEEToFloat iee = IEEToFloat(signoSuma, exponenteSuma, conversorEnteros(mantisaSumaNormalizada));
    return iee.getNumber();
}

Multiplicacion::Multiplicacion(){

}

float Multiplicacion::comaFlotante(int signoA, int exponenteA, int mantisaA, int signoB, int exponenteB, int mantisaB) {
    //PASO 1
    int signoProducto = signoA * signoB;

    // PASO 2
    int exponenteProducto = (exponenteA-127) + (exponenteB-127) + 127;

    // PASO 3
    MultiplicacionSinSigno resultSinSigno = MultiplicacionSinSigno(mantisaA, mantisaB);
    int * A = resultSinSigno.getA();
    int * P = resultSinSigno.getP();
    if(P[0] == 0) {
        int auxA = A[0];
        A = desplazarBitsIzquierda(A, true, 1);
        P = desplazarBitsIzquierda(P, auxA == 0, 1);
    } else {
        exponenteProducto++;
    }

    int r = A[0];
    int st = 0;
    for(int i = 0; i < 23; i++) {
        if(A[i+1] == 1) {
            st = 1;
        }
    }

    int c = 0;
    if((r == 1 && st == 1) || (r == 1 && st == 0 && P[23] == 1)) {
        // HAY QUE SUMAR 1 a P
        //P = sumaBinario(P, 1, c);
    }


    // DESBORDAMIENTOS
    // 1
    if(exponenteProducto > MAX_REPRESENTABLE) {
        return 0;
    }
    // 2
    int t;
    if(exponenteProducto < EXPONENTE_MINIMO) {
        t = EXPONENTE_MINIMO - exponenteProducto;
        if (t > TAM_MANTISA) {
            return 0;
        } else {
            A = desplazarBitsDerecha(A, true, t);
            P = desplazarBitsDerecha(P, true, t);
            exponenteProducto = EXPONENTE_MINIMO;
        }
    }
    int t1;
    int t2;
    if (exponenteProducto > EXPONENTE_MINIMO) {
        t1 = exponenteProducto - EXPONENTE_MINIMO;
        t2 = mantisaNormalizada(P);
        if (t1 < t2) t = t1;
        else t = t2;
        exponenteProducto -= t;
        P = desplazarBitsIzquierda(P, true, t);
        A = desplazarBitsIzquierda(A, true, t);
    } else if (exponenteProducto == EXPONENTE_MINIMO) {

    }

    // OPERANDOS 0

    return 0;
}

MultiplicacionSinSigno::MultiplicacionSinSigno(int mantisaA, int mantisaB) {
    // PASO 1
    int i;
    int * A = conversorBinario(mantisaA, 23);
    int * B = conversorBinario(mantisaB, 23);
    int * P = new int[24];
    for(i = 0; i < 24; i++){
        P[i] = 0;
    }

    // PASO 2
    for(i = 0; i < 24; i++) {
        int c = 0;
        if(A[23] == 1) {
            P = sumaBinario(P, B, c);
        }
        int aux = P[23];
        P = desplazarBitsDerecha(P, c == 0, 1);
        A = desplazarBitsDerecha(A, aux == 0, 1);
    }

    // PASO 3
    // CONSISTE EN DEVOLVER EL RESULTADO ES DECIR A Y B
}

int * MultiplicacionSinSigno:: getP(){
    return this->P;
}

int * MultiplicacionSinSigno:: getA(){
    return this->A;
}

Division::Division(){

}

float Division::divisionCompaFlotante(int signoA, int exponenteA, int mantisaA, int signoB, int exponenteB, int mantisaB){
    int * mantisaABinaria = new int[23];
    int * mantisaBBinaria = new int[23];
    mantisaABinaria = conversorBinario(mantisaA, 23);
    mantisaBBinaria = conversorBinario(mantisaB, 23);

    int * mantisaABinariaFinal = new int[24];
    int * mantisaBBinariaFinal = new int[24];
    for(int i=0; i<23; i++){
        mantisaABinariaFinal[i+1] = mantisaABinaria[i];
        mantisaBBinariaFinal[i+1] = mantisaBBinaria[i];
    }
    float mantisaADecimal = conversorDecimal(mantisaABinaria);
    float mantisaBDecimal = conversorDecimal(mantisaBBinaria);
    mantisaADecimal += 1;
    mantisaBDecimal += 1;
    qDebug() << mantisaADecimal;
    qDebug() << mantisaBDecimal;
    return 0;
}




















