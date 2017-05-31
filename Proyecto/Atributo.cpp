#include "Atributo.hpp"


Atributo::Atributo(string a,string t,string l) {
    atributo=a;
    tipo=t;
    valores=l;
}
Atributo::Atributo(string a,string t) {
    atributo=a;
    tipo=t;
    valores="";
}
string Atributo::getValores(){
	return valores;
}
string Atributo::getTipo(){
	return tipo;
}

string Atributo::getAtributo(){
	return atributo;
}
