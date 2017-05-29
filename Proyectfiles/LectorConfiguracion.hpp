#ifndef __LECTORCONFIGURACION
#define __LECTORCONFIGURACION

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>
#include <stdlib.h>
#include "Atributo.hpp"
#include "Hecho.hpp"
#include "Regla.hpp"

using namespace std;

class LectorConfiguracion {

  int nAtributos;
  list<Atributo*> listaAtributo;
  string objetivo;
  int nReglas;
  list<int> listaprioridades;

      public:

       LectorConfiguracion();  // Constructor
       void leer(string file);
       list<int> getListaprioridades();
       string getObjetivo();
       list<Atributo*> getAtributos();


};



class LectorBC {

  string dominioAplicacion;
  int nReglas;
  list<Regla*> listaReglas;

  public:

       LectorBC();  // Constructor
       void leer(string file,LectorConfiguracion* lc);
       list<Regla*> getListaReglas();
       string getDominio();

};

class LectorBH {

  int nHechos;
  list<Hecho*> listaHechos;
  list<Regla*> ConjuntoConflicto;
  public:

       LectorBH();  // Constructor
       void leer(string file);
       list<Hecho*> getListaHechos();
       void ejecutar(LectorBC* bc, LectorConfiguracion* lc);
       void funcionConjuntoConflicto(list<Regla*> listaR,list<Atributo*> lis);
       void equiparacion(list<Regla*> listaR);
       Regla* resolver(list<Regla*> listaR);
       Hecho* aplicar(Regla* r);
       void imprimirBaseHechos(LectorConfiguracion* lc,LectorBC* bc);
       bool comprobarContenida(string ob);
       string comprobarTipo(Hecho* h2,list<Atributo*>listaA);



};

#endif
