#ifndef __REGLA
#define __REGLA

#include "Hecho.hpp"
#include <set> //TODO
#include <list>

using namespace std;

/**
 * Clase Regla para representar las reglas de nuestro sistema. Tenemos los literales A y B como
 * se denota en la especificacion.
**/
class Regla {
      string identificador;
      int prioridad;
      list<Hecho*> A;
      Hecho* B;

      public:
             Regla(string id,int p,list<Hecho*> A,Hecho* B);
             string getId();
             int getPrioridad();
             void setPrioridad(int);
             list<Hecho*> getA();
             Hecho* getB();
             string printRegla();

};

#endif
