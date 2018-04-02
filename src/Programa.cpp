//
// Created by power on 30/03/18.
//

#include "Programa.h"

Progama::Programa(){
}


void Programa::agregarInstruccion(Id idRutina, Instruccion instruccion) {
    for (i=0; i<instrucciones.size(); i++){  //acá no tengo claros los objetos.
        idRutina.pushback(instruccion);
        if (esRutinaExistente(idRutina) == false){
            rutinas.nombre = idRutina;
        }
    }

} //Esto creo que va al revés.


bool Programa::esRutinaExistente(Id idRutina) const {
    for (i=0; i<rutina.size(); i++){
        if (rutina[i] == _rutina[i]){
            existeRutina = true;
        } else {
            existeRutina = false;
        }

    }

}

Instruccion Programa::instruccion(Id idRutina, int i) const {
        if (i>=0 and i<idRutina.size() and esRutinaExistente(idRutina) == true){
            return idRutina[i];
        }


}


int Programa::longitud(Id idRutina) const {
    if (esRutinaExistente() == true) {
        return idRutina.size();
    }
}




