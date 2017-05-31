#include "Hecho.hpp"


 Hecho::Hecho(string n, string v, string o) {
    nombre=n;
    valor=v;
    op=o;
}
void Hecho::addNombre(string n) {
     nombre = n;
}



void Hecho::addValor(string v) {
     valor = v;
}


string Hecho::getNombre() {
     return nombre;
}

string Hecho::getValor(){
     return valor;
}

string Hecho::getOp(){
     return op;
}

string Hecho::printHecho(){
  string h;
  h = nombre +" "+ op+ " " + valor ;
 return h;
}
