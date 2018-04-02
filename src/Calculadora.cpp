//
// Created by power on 30/03/18.
//

#include "Calculadora.h"

Calculadora::Calculadora(Programa programa){
    _programa = programa;
    _memoria = vector<variable>();
    _pila = stack<int>();
}

int indice(Id idVariable){
    bool encontrado = false;
    int i = 0;
    int res = -1;
     while(!encontrado && i<_memoria.size()){
         if(_memoria[i].nombre == idVariable){
             res = i;
             encontrado = true;
         }

         i++;
     }
     return res;
}

void Calculadora::asignarVariable(Id idVariable, int valor) {

    int ind =  indice(idVariable);
    if(  ind > -1){
        _memoria[ind].valor = valor;
    }else{
        struct variable;
        variable.nombre = idVariable;
        variable.valor = valor;
        //se agrega la variable a al memoria
        _memoria.pushback(variable);
    }

}

void Calculadora::ejecutar(Id idRutina) {
    //TODO
}

int Calculadora::valorVariable(Id idVariable) const {
    int ind = indice(idVariable);
    if(ind > -1){
        return _memoria[ind].valor;
    } else {
        return 0;
    }
}

void push(int valor){

}
void add(int v1, int v2){

}
void sub(int v1, int v2){

}
void mul(int v1, v2){

}
void read (Id idVariable){

}
void write(Id idVariable){

}
//jump
//jumpz

