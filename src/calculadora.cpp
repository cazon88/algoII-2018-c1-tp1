#include "Calculadora.h"

Calculadora::Calculadora(Programa programa){
    _programa = programa;
    _memoria = std::vector<variable>();
    _pila = std::stack<int>();
}

int Calculadora::indice(Id idVariable) const{
    bool encontrado = false;
    int i = 0;
    int res = -1;
    while(!encontrado && i< _memoria.size()){
        if( _memoria[i].nombre == idVariable){
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
        struct variable var;
        var.nombre = idVariable;
        var.valor = valor;
        //se agrega la variable a al memoria
        _memoria.push_back(var);
    }

}

int Calculadora::valorVariable(Id idVariable) const {
    int ind = indice(idVariable);
    if(ind > -1){
        return _memoria[ind].valor;
    } else {
        return 0;
    }
}


 void Calculadora::ejecutar(Id idRutina) {

    bool llegoAlFinalDeLaRutina = false;

    if(_programa.esRutinaExistente(idRutina) && !llegoAlFinalDeLaRutina){
        for(int i = 0; i < _programa.longitud(idRutina); i++) {
            Instruccion instruc = _programa.instruccion(idRutina, i);
            switch (instruc.operacion()) {
                case PUSH  :
                    push(instruc.valor());
                    break;
                case ADD  :
                    add();
                    break;
                case SUB  :
                    sub();
                    break;
                case MUL  :
                    mul();
                    break;
                case READ  :
                    read(instruc.nombre());
                    break;
                case WRITE  :
                    write(instruc.nombre());
                    break;
                case JUMP  :
                    i = _programa.longitud(idRutina); // para cortar la iteracion de instrucciones.
                    ejecutar(instruc.nombre()); //Ejecuta la nueva rutina
                    break;
                case JUMPZ  :
                    if (_pila.empty() || _pila.top() == 0) {
                        i = _programa.longitud(idRutina); // para cortar la iteracion de instrucciones.
                        ejecutar(instruc.nombre()); //Ejecuta la nueva rutina
                    }
                    break;
            }
        }

        llegoAlFinalDeLaRutina = true;
    }
}


/****** Operaciones aritmeticas ******/


//Mete una constante numerica en la pila
void Calculadora::push(int valor){
    _pila.push(valor);
}

int Calculadora::obtenerValor(){
    int res = _pila.top();
    _pila.pop();
    return res;
}

//Saca dos valores del tope de la pila, los suma y los vuelve a agregar.
void Calculadora::add(){

    if(!_pila.empty()){
        int suma =   obtenerValor();
        suma += _pila.empty() ? 0 :obtenerValor();
        _pila.push(suma);
    }else{
        _pila.push(0);
    }

}

//Saca dos valores del tope de la pila, los resta y los vuelve a agregar.
void Calculadora::sub(){

    if(!_pila.empty()){
        int resta =   obtenerValor();
        resta = ( _pila.empty() ? 0 :obtenerValor() ) - resta;
        _pila.push(resta );
    }else{
        _pila.push(0);
    }
}

//Saca dos valores del tope de la pila, los multiplica y los vuelve a agregar.
void Calculadora::mul() {

    if (!_pila.empty()) {
        int multiplicacion = obtenerValor();
        multiplicacion *= _pila.empty() ? 0 : obtenerValor();
        _pila.push(multiplicacion);
    } else {
        _pila.push(0);
    }
}

/****** Operaciones de manejo de variables ******/

void Calculadora::write (Id idVariable){

    int valorNuevo = 0;

    if (!_pila.empty()){
        valorNuevo =  obtenerValor();
    }

    int ind = indice(idVariable);
    if (ind < 0){
        struct variable var;
        var.nombre = idVariable;
        var.valor = valorNuevo;
        _memoria.push_back(var);
    }else{
        _memoria[ind].valor = valorNuevo;
    }
}


void Calculadora::read(Id idVariable){

    int valor = 0;

    int ind = indice(idVariable);
    if (ind > -1){
        valor = _memoria[ind].valor;
    }

    _pila.push(valor);
}