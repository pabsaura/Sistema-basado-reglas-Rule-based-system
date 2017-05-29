#include "Regla.hpp"

/**
 * Constructor de la clase Regla, se le pasa como par�metro el identificador
 * de tipo entero de la regla.
 *
**/
Regla::Regla(string id,int p,list<Hecho*> list1,Hecho* hechoB) {
     identificador = id;
     prioridad=p;
     B=hechoB;
     A=list1;
}

string Regla::getId() {
    return identificador;
}



int Regla::getPrioridad() {
    return prioridad;
}


void Regla::setPrioridad(int p) {
    prioridad = p;
}


list<Hecho*> Regla::getA() {
     return A;
}

Hecho* Regla::getB() {
     return B;
}


string Regla::printRegla(){
  string r;
  r = identificador + " ";
  r += "Si ";
  int contador = 0;
  for(std::list<Hecho*>::iterator list_iter = A.begin();
     list_iter != A.end(); list_iter++){
        //Recorremos los hechos de la regla
        if(contador>0)r+=" Y ";

       Hecho *h1 = *list_iter;
       r += h1->printHecho();
       contador++;
     }
    r+= " Entonces ";
  r += B->printHecho();
  return r;

}
