#ifndef __ATRIBUTO
#define __ATRIBUTO

//#include "Tipo.hpp"
#include <list>
#include <string>

using namespace std;

/**
 * Clase Atributo para representar los atributos del fichero configuracion.
**/
class Atributo {

      string atributo;
      string tipo;
      string valores;

    public:
           Atributo(string a, string t, string l);  // Constructor
           Atributo(string a, string t);
			string getValores();
			string getTipo();
			string getAtributo();
};

#endif
