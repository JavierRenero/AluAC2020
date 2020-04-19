#include "iee754converter.h"
#include <QString>

floatToIEE::floatToIEE(float number)
{
    this->a.numero = number;
}

int floatToIEE::getSigno(){
    return this->a.bitfield.sign;
}

int floatToIEE::getExponente(){
    return this->a.bitfield.expo;
}

int floatToIEE::getFraccionaria(){
    return this->a.bitfield.partFrac;
}

IEEToFloat::IEEToFloat(int signo, int exponente, int fraccionaria)
{
    this->a.bitfield.sign = signo;
    this->a.bitfield.expo = exponente;
    this->a.bitfield.partFrac = fraccionaria;
}

float IEEToFloat::getNumber(){
    return this->a.numero;
}
