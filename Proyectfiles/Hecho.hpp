#ifndef __HECHO
#define __HECHO

#include <iostream>

using namespace std;

/**
 * Clase Hecho que representa los hechos de la base del conocimiento y tambien los literales
 * en la base de hechos.
**/
class Hecho {
      string nombre;
      string valor;
      string op;
      public:
              Hecho(string n, string v,string o);
             void addNombre(string); // TODO
             void addValor(string);
             string getNombre();
             string getValor();
             string getOp();
             bool iguales(Hecho* h);
             string printHecho();
};

#endif
