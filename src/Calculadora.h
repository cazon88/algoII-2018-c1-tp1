#ifndef __CALCULADORA_H__
#define __CALCULADORA_H__

#include "Programa.h"
#include <stack>


class Calculadora {
public:

Calculadora(Programa programa);

void asignarVariable(Id idVariable, int valor);

void ejecutar(Id idRutina);

int valorVariable(Id idVariable) const;


private:
    Programa _programa;
    std::vector<variable> _memoria;
    std::stack<int> _pila;

    int indice(Id idVariable) const;
    int indiceRutina(Id idRtina);
    int obtenerValor();

    void push(int valor);
    void add();
    void sub();
    void mul();

    void read (Id idVariable);
    void write (Id idVariable);
};


#endif /*__CALCULADORA_H__*/
