//
// Created by power on 30/03/18.
//

#ifndef SOLUCION_CALCULADORA_H
#define SOLUCION_CALCULADORA_H
#include Programa.h



class Calculadora {
public:

Calculadora(Programa programa);

void asignarVariable(Id idVariable, int valor);

void ejecutar(Id idRutina);

int valorVariable(Id idVariable) const;


};


#endif //SOLUCION_CALCULADORA_H
