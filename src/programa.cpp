#include "Programa.h"

Programa::Programa(){
    _rutinas = std::vector<rutina>(); // DUDA: creamos bien el vector vacio?
}


void Programa::agregarInstruccion(Id idRutina, Instruccion instruccion) {

    if (!esRutinaExistente(idRutina)){
        //creo rutina
        rutina r;
        r.nombre = idRutina;
        r.instrucciones = std::vector<Instruccion>();
        r.instrucciones.push_back(instruccion);
        //Se agegra a _rutinas
        _rutinas.push_back(r);
    }else{
        //Si existe, se busca la rutnia y se agrega la instruccion
        bool encontrado = false;
        int i = 0;

        while(i< _rutinas.size() and !encontrado)
        {
            if(_rutinas[i].nombre == idRutina){
                encontrado = true;
                _rutinas[i].instrucciones.push_back(instruccion);
            }

            i++;
        }
    }


}


bool Programa::esRutinaExistente(Id idRutina) const {

    bool existeRutina = false;

    for (int i=0; i< _rutinas.size(); i++){
        if (_rutinas[i].nombre == idRutina){
            existeRutina = true;
        }
    }

    return existeRutina;

}

Instruccion Programa::instruccion(Id idRutina, int i) const {
    for(int j=0; j<_rutinas.size(); j++){
        if(_rutinas[j].nombre == idRutina){
            return _rutinas[j].instrucciones[i];
        }
    }
}


int Programa::longitud(Id idRutina) const {
    for(int i=0; i<_rutinas.size(); i++){
        if(_rutinas[i].nombre == idRutina){
            return _rutinas[i].instrucciones.size();
        }
    }
}