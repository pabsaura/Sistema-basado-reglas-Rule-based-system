#include "LectorConfiguracion.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char **argv) {
    string file,file2,file3;
    LectorConfiguracion* lc = new LectorConfiguracion;
    LectorBC* bc = new LectorBC;   // Creamos el Motor de inferencia
    LectorBH*bh = new LectorBH;

    file = argv[1];
    file2 = argv[2];
    file3 = argv[3];
    //cout << "Elija el fichero de configuracion: ";
    //cin >> file;
    lc->leer(file);
    //cout << "Elija el fichero con la base de conocimiento: ";         // Leemos los ficheros
    //cin >> file2;
    bc->leer(file2,lc);
    //cout << "Elija el fichero con la base de hechos: ";
    //cin >> file3;
    bh->leer(file3);

    bh->ejecutar(bc,lc);
  cout<< "-----Termina-----" <<endl;
  system("pause");
    return 0;
}
