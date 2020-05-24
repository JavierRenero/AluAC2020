#include "operaciones.h"
#include "iee754converter.h"
#include "math.h"
#define MAX_REPRESENTABLE 254
#define EXPONENTE_MINIMO 0
#define TAM_MANTISA 24

// Convierte un numero binario a complemento a2
int *Operaciones::complemento2(int binario[]) {
  for (int i = 0; i < 24; i++) {
    if (binario[i] == 1) {
      binario[i] = 0;
    } else {
      binario[i] = 1;
    }
  }
  int c = 0;
  int *suma1 = new int[24];
  for (int i = 0; i < 23; i++) {
    suma1[i] = 0;
  }
  suma1[23] = 1;
  binario = sumaBinario(binario, suma1, c);
  return binario;
}

// Convierte un numero entero a binario
int *Operaciones::conversorBinario(int decimal, int tam) {
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

// Devuelve un vector con n desplazamientos a la derecha añadiendo unos o ceros
int *Operaciones::desplazarBitsDerecha(int binario[], bool ceros,
                                       int desplazamientos) {
  int contador = 0;
  int sustituto = 1;
  if (ceros)
    sustituto = 0;
  while (contador < desplazamientos) {
    for (int i = 24; i > 0; i--) {
      binario[i] = binario[i - 1];
    }
    contador++;
    binario[0] = sustituto;
  }
  return binario;
}

// Devuelve un vector con n desplazamientos a la izquierda añadiendo unos o ceros
int *Operaciones::desplazarBitsIzquierda(int binario[], bool ceros,
                                         int desplazamientos) {
  int contador = 0;
  int sustituto = 1;
  if (ceros)
    sustituto = 0;
  while (contador < desplazamientos) {
    for (int i = 0; i < 24; i++) {
      binario[i] = binario[i + 1];
    }
    contador++;
    binario[23] = sustituto;
  }
  return binario;
}

// Devuelve la suma de los dos numeros en binario
int *Operaciones::sumaBinario(int binario1[], int binario2[], int &acarreo) {
  int *resultado = new int[24];
  for (int i = 23; i >= 0; i--) {
    resultado[i] = (binario1[i] + binario2[i] + acarreo) % 2;
    if (binario1[i] + binario2[i] + acarreo > 1)
      acarreo = 1;
    else
      acarreo = 0;
  }
  return resultado;
}

// Devulve el numero de posiciones que hay que desplazar para que la mantisa sea normalizada
int Operaciones::mantisaNormalizada(int binario[]) {
  int contador = 0;
  while (contador < 24) {
    if (binario[contador] == 1)
      return contador;
    contador++;
  }
  return contador;
}

// Devulvle el numero en un entero
int Operaciones::conversorEnteros(int binario[]) {
  int decimal = 0;
  int contador = 0;
  for (int i = 22; i >= 0; i--) {
    if (binario[i] == 1) {
      decimal += pow(2, contador);
    }
    contador++;
  }
  return decimal;
}

// Devulve el numero en decimal
float Operaciones::conversorDecimal(int binario[]) {
  float decimal = 0;
  int contador = -1;
  for (int i = 0; i < 23; i++) {
    if (binario[i] == 1) {
      decimal += pow(2, contador);
    }
    contador--;
  }
  return decimal;
}

Suma::Suma() {
  // PASO 1
  this->g = 0;
  this->r = 0;
  this->st = 0;
  this->n = 24;
  this->operandosIntercambiados = false;
  this->complemento_P = false;
}

// Realiza la suma de dos numeros binarios en formato IEE754
QString Suma::realizarSuma(int signoA, int exponenteA, int mantisaA, int signoB,
                           int exponenteB, int mantisaB) {
  // PASO 2
  if (exponenteA < exponenteB) {
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

  // PASO 3
  int exponenteSuma = exponenteA;
  int d = exponenteA - exponenteB;

  // PASO 4 Y PASO 5
  int *mantisaBBinaria = new int[24];
  // Pasamos la mantisa a binario
  mantisaBBinaria = conversorBinario(mantisaB, 24);
  mantisaBBinaria[0] = 1;

  if (signoA != signoB) {
    mantisaBBinaria = complemento2(mantisaBBinaria);
  }

  // PASO 6
  if (22 - d + 1 < 23) {
    g = mantisaBBinaria[d];
  }
  if (22 - d + 2 < 23) {
    r = mantisaBBinaria[d - 1];
  }
  int n = 2;
  while (23 - d + n < 23) {
    if (mantisaBBinaria[d - n] == 1) {
      st = 1;
    }
    n++;
  }

  // PASO 7
  if (signoA != signoB) {
    mantisaBBinaria = desplazarBitsDerecha(mantisaBBinaria, false, d);
  } else {
    mantisaBBinaria = desplazarBitsDerecha(mantisaBBinaria, true, d);
  }

  // PASO 8
  int *mantisaABinaria = conversorBinario(mantisaA, 24);
  mantisaABinaria[0] = 1;
  int acarreo = 0;
  mantisaBBinaria = sumaBinario(mantisaABinaria, mantisaBBinaria, acarreo);

  // PASO 9
  if (signoA != signoB && mantisaBBinaria[0] == 1 && acarreo == 0) {
    mantisaBBinaria = complemento2(mantisaBBinaria);
    complemento_P = true;
  }

  // PASO 10
  if (signoA == signoB && acarreo == 1) {
    if (g || r || st == 0) {
      st = 0;
    } else {
      st = 1;
    }
    r = mantisaBBinaria[this->n - 1];
    mantisaBBinaria = desplazarBitsDerecha(mantisaBBinaria, false, 1);
    exponenteSuma++;
  } else {
    int k = mantisaNormalizada(mantisaBBinaria);
    if (k == 0) {
      if (r || st == 0)
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

  // PASO 11
  int c2 = 0;
  if ((r == 1 && st == 1) || (r == 1 && st == 0 && mantisaBBinaria[23] == 1)) {
    int *suma1 = new int[24];
    for (int i = 0; i < 23; i++) {
      suma1[i] = 0;
    }
    suma1[23] = 1;
    mantisaBBinaria = sumaBinario(mantisaBBinaria, suma1, c2);
    if (c2 == 1) {
      mantisaBBinaria = desplazarBitsDerecha(mantisaBBinaria, true, 1);
      exponenteSuma++;
    }
  }

  int *mantisaSumaNormalizada = new int[23];
  for (int i = 22; i >= 0; i--) {
    mantisaSumaNormalizada[i] = mantisaBBinaria[i + 1];
  }

  // PASO 12
  int signoSuma;
  if (!operandosIntercambiados && complemento_P) {
    signoSuma = signoB;
  } else {
    signoSuma = signoA;
  }
  if (exponenteSuma > 254) {
    return "Inf";
  }

  if (exponenteSuma < EXPONENTE_MINIMO) {
    return "-Inf";
  }

  // PASO 13
  IEEToFloat iee = IEEToFloat(signoSuma, exponenteSuma,
                              conversorEnteros(mantisaSumaNormalizada));
  return QString::number(iee.getNumber());
}

Multiplicacion::Multiplicacion() {}

// Realiza la multiplicación de dos numeros binarios en formato IEE754
QString Multiplicacion::realizarMultiplicacion(int signoA, int exponenteA, int mantisaA,
                                     int signoB, int exponenteB, int mantisaB) {
  // PASO 1
  int signoProducto = signoA ^ signoB;

  // PASO 2
  int exponenteProducto = (exponenteA - 127) + (exponenteB - 127) + 127;

  // PASO 3
  MultiplicacionSinSigno resultSinSigno =
      MultiplicacionSinSigno(mantisaA, mantisaB);
  int *A = resultSinSigno.getA();
  int *P = resultSinSigno.getP();
  if (P[0] == 0) {
    int *resultado = new int[48];
    resultado = juntarPA(P, A);
    resultado = desplazarBitsIzquierda(resultado, true, 1);
    P = separarP(resultado);
    A = separarA(resultado);
  } else {
    exponenteProducto++;
  }

  int r = A[0];
  int st = 0;
  for (int i = 0; i < 23; i++) {
    if (A[i + 1] == 1) {
      st = 1;
    }
  }

  if ((r == 1 && st == 1) || (r == 1 && st == 0 && P[23] == 1)) {
    // HAY QUE SUMAR 1 a P
    int c = 0;
    int *suma1 = new int[24];
    for (int i = 0; i < 23; i++) {
      suma1[i] = 0;
    }
    suma1[23] = 1;
    P = sumaBinario(P, suma1, c);
  }
  // DESBORDAMIENTOS
  // 1
  int t;
  int *resultado = new int[48];
  if (exponenteProducto > MAX_REPRESENTABLE) {
    return "Inf";
  } else if (exponenteProducto < EXPONENTE_MINIMO) {
    t = EXPONENTE_MINIMO - exponenteProducto;
    if (t >= TAM_MANTISA) {
      return "-Inf";
    } else {
      resultado = juntarPA(P, A);
      resultado = desplazarBitsDerecha(resultado, signoProducto == 0, t);
      exponenteProducto = EXPONENTE_MINIMO;
    }
  }
  int t1;
  int t2;
  if (exponenteProducto > EXPONENTE_MINIMO) {
    t1 = exponenteProducto - EXPONENTE_MINIMO;
    resultado = juntarPA(P, A);
    t2 = mantisaNormalizada(resultado);
    if (t1 < t2)
      t = t1;
    else
      t = t2;
    exponenteProducto -= t;
    resultado = desplazarBitsIzquierda(resultado, true, t);

  } else if (exponenteProducto == EXPONENTE_MINIMO) {
    return "Denormal";
  }
  P = separarP(resultado);
  A = separarA(resultado);
  int *resultadoMult = new int[24];
  for (int i = 22; i >= 0; i--) {
    resultadoMult[i] = P[i + 1];
  }
  IEEToFloat iee = IEEToFloat(signoProducto, exponenteProducto,
                              conversorEnteros(resultadoMult));

  return QString::number(iee.getNumber());
}

// Devuelve un vector formado por P y A
int *Multiplicacion::juntarPA(int P[], int A[]) {
  int *resultado = new int[48];
  for (int i = 0; i < 48; i++) {
    if (i < 24) {
      resultado[i] = P[i];
    } else {
      resultado[i] = A[i];
    }
  }

  return resultado;
}

// Separa P
int *Multiplicacion::separarP(int *PA) {
  int *resultado = new int[24];
  for (int i = 0; i < 24; i++) {
    resultado[i] = PA[i];
  }
  return resultado;
}

// Separa A
int *Multiplicacion::separarA(int *PA) {
  int *resultado = new int[24];
  for (int i = 0; i < 24; i++) {
    resultado[i] = PA[i + 24];
  }
  return resultado;
}

// Realiza la multiplicación de dos mantisas
MultiplicacionSinSigno::MultiplicacionSinSigno(int mantisaA, int mantisaB) {
  // PASO 1
  int i;
  A = conversorBinario(mantisaA, 24);
  B = conversorBinario(mantisaB, 24);
  P = new int[24];
  for (i = 0; i < 24; i++) {
    P[i] = 0;
  }

  // PASO 2
  for (i = 0; i < 24; i++) {
    int c = 0;
    if (A[23] == 1) {
      P = sumaBinario(P, B, c);
    }
    int aux = P[23];
    P = desplazarBitsDerecha(P, c == 0, 1);
    A = desplazarBitsDerecha(A, aux == 0, 1);
  }
  // PASO 3
  // CONSISTE EN DEVOLVER EL RESULTADO ES DECIR A Y B
}

int *MultiplicacionSinSigno::getP() { return this->P; }

int *MultiplicacionSinSigno::getA() { return this->A; }

int *MultiplicacionSinSigno::getB() { return this->B; }

Division::Division() {}

// Realiza la división de dos numeros binarios en formato IEE754
QString Division::realizarDivision(int signoA, int exponenteA,
                                        int mantisaA, int signoB,
                                        int exponenteB, int mantisaB) {
  int *mantisaABinaria = new int[24];
  int *mantisaBBinaria = new int[24];

  mantisaABinaria = conversorBinario(mantisaA, 24);
  mantisaBBinaria = conversorBinario(mantisaB, 24);

  int *mantisaABinariaFinal = new int[23];
  int *mantisaBBinariaFinal = new int[23];

  for (int i = 0; i < 23; i++) {
    mantisaABinariaFinal[i] = mantisaABinaria[i + 1];
    mantisaBBinariaFinal[i] = mantisaBBinaria[i + 1];
  }

  float mantisaADecimal = conversorDecimal(mantisaABinariaFinal);
  float mantisaBDecimal = conversorDecimal(mantisaBBinariaFinal);

  mantisaADecimal += 1;
  mantisaBDecimal += 1;

  float bPrima;
  int exponenteDivision;
  if (mantisaBDecimal < 1.25) {
    bPrima = 1;
  } else {
    bPrima = 0.80;
  }

  int signoDivision = signoA ^ signoB;

  floatToIEE A = floatToIEE(mantisaADecimal);
  floatToIEE B = floatToIEE(mantisaBDecimal);
  floatToIEE BP = floatToIEE(bPrima);

  Multiplicacion mult = Multiplicacion();

  float x0 =
      mult.realizarMultiplicacion(A.getSigno(), A.getExponente(), A.getFraccionaria(),
                        BP.getSigno(), BP.getExponente(), BP.getFraccionaria())
          .toFloat();
  float y0 =
      mult.realizarMultiplicacion(B.getSigno(), B.getExponente(), B.getFraccionaria(),
                        BP.getSigno(), BP.getExponente(), BP.getFraccionaria())
          .toFloat();

  Suma sum = Suma();
  floatToIEE dos = floatToIEE(2);
  floatToIEE y0IEENeg = floatToIEE(-y0);

  // Calculamos R inicial
  float r =
      sum.realizarSuma(dos.getSigno(), dos.getExponente(),
                       dos.getFraccionaria(), y0IEENeg.getSigno(),
                       y0IEENeg.getExponente(), y0IEENeg.getFraccionaria())
          .toFloat();
  floatToIEE rIEE = floatToIEE(r);
  floatToIEE x0IEE = floatToIEE(x0);
  floatToIEE y0IEEPos = floatToIEE(y0);

  // Calculamos Y0 inicial
  y0 = mult.realizarMultiplicacion(y0IEEPos.getSigno(), y0IEEPos.getExponente(),
                         y0IEEPos.getFraccionaria(), rIEE.getSigno(),
                         rIEE.getExponente(), rIEE.getFraccionaria())
           .toFloat();

  // Calculamos X1 inicial
  float x1 = mult.realizarMultiplicacion(x0IEE.getSigno(), x0IEE.getExponente(),
                               x0IEE.getFraccionaria(), rIEE.getSigno(),
                               rIEE.getExponente(), rIEE.getFraccionaria())
                 .toFloat();
  floatToIEE x1IEE = floatToIEE(x1);
  floatToIEE x0IEENeg = floatToIEE(-x0);

  // Bucle para ajustar el valor de x1
  while (
      abs(sum.realizarSuma(x1IEE.getSigno(), x1IEE.getExponente(),
                           x1IEE.getFraccionaria(), x0IEENeg.getSigno(),
                           x0IEENeg.getExponente(), x0IEENeg.getFraccionaria())
              .toFloat()) > 10E-4) {
    x0 = x1;
    x0IEE = floatToIEE(x0);
    x0IEENeg = floatToIEE(-x0);
    floatToIEE y0IEENeg = floatToIEE(-y0);
    floatToIEE y0IEEPos = floatToIEE(y0);
    // Recalculamos R
    r = sum.realizarSuma(dos.getSigno(), dos.getExponente(),
                         dos.getFraccionaria(), y0IEENeg.getSigno(),
                         y0IEENeg.getExponente(), y0IEENeg.getFraccionaria())
            .toFloat();
    floatToIEE rIEE = floatToIEE(r);
    // Recalculamos Y0
    y0 = mult.realizarMultiplicacion(y0IEEPos.getSigno(), y0IEEPos.getExponente(),
                           y0IEEPos.getFraccionaria(), rIEE.getSigno(),
                           rIEE.getExponente(), rIEE.getFraccionaria())
             .toFloat();
    // Recalculamos X1
    x1 = mult.realizarMultiplicacion(x0IEE.getSigno(), x0IEE.getExponente(),
                           x0IEE.getFraccionaria(), rIEE.getSigno(),
                           rIEE.getExponente(), rIEE.getFraccionaria())
             .toFloat();
  }

  floatToIEE xiIEE = floatToIEE(x1);

  // Calculamos el exponente de la división
  exponenteDivision =
      (exponenteA - 127) - (exponenteB - 127) + xiIEE.getExponente();
  IEEToFloat resultado =
      IEEToFloat(signoDivision, exponenteDivision, xiIEE.getFraccionaria());
  return QString::number(resultado.getNumber());
}
