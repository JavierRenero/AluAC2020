#ifndef IEE754CONVERTER_H
#define IEE754CONVERTER_H


union Code {
    struct{
        unsigned int partFrac : 23;
        unsigned int expo : 8;
        unsigned int sign : 1;
    }bitfield;

    float numero;
    unsigned int numerox;
};

class floatToIEE
{
public:
    floatToIEE();
    floatToIEE(float number);
    int getSigno();
    int getExponente();
    int getFraccionaria();
private:
    union Code a;
};

class IEEToFloat
{
public:
    IEEToFloat();
    IEEToFloat(int signo, int exponente, int fraccionaria);
    float getNumber();
private:
    union Code a;
};

#endif // IEE754CONVERTER_H
