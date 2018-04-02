//
// Created by power on 30/03/18.
//

#include "Programa.h"

Progama::Programa(){
    _rutinas = vector<rutina>(); // DUDA: creamos bien el vector vacio?
}


void Programa::agregarInstruccion(Id idRutina, Instruccion instruccion) {

    if (!esRutinaExistente(idRutina)){
        //creo rutina
        rutina r;
        r.nombre = idRutina;
        r.instrucciones = vector<instruccion>();
        r.instrucciones.pushback(instruccion);
        //Se agegra a _rutinas
        _rutinas.pushback(r);
    }else{
        //Si existe, se busca la rutnia y se agrega la instruccion
        bool encontrado = false;
        int i = 0;

        while(i< _rutinas.size() and !encontrado)
        {
            if(_rutinas[i].nombre == idRutina){
                encontrado = true;
                _rutinas[i].instrucciones.pushback(instruccion);
            }

            i++;
        }
    }


}


bool Programa::esRutinaExistente(Id idRutina) const {

    bool existeRutina = false;

    for (i=0; i< _rutinas.size(); i++){
        if (_rutinas[i].nombre == idRutina){
            existeRutina = true;
        }
    }

    return existeRutina;

}

Instruccion Programa::instruccion(Id idRutina, int i) const {
    for(j=0; j<_rutinas.size(); j++){
        if(_rutinas[j].nombre == idRutina){
            return _rutinas[j].instrucciones[i];
        }
    }
}


int Programa::longitud(Id idRutina) const {
    for(i=0; i<_rutinas.size(); i++){
        if(_rutinas[i].nombre == idRutina){
            return _rutinas[i].instrucciones.size();
        }
    }
}





