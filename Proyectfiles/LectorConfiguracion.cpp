#include "LectorConfiguracion.hpp"

/**
 * Constructor de la clase lectorConfiguracion

**/

ofstream fs("salida.txt",std::ofstream::trunc);
string globalObjetivo;

LectorConfiguracion::LectorConfiguracion() {
  nAtributos=0;
  objetivo="";
  nReglas=0;
}


void LectorConfiguracion::leer(string file) {
  ifstream configuracion(file.c_str(), ifstream::in);
  string atributo;
  string tipo;
  string valor;
  string valorObjetivo;
  string prioridad;
  int valorPrioridad;
  int numeroReglas;

  configuracion >> atributo;

  if (atributo == "ATRIBUTOS"){
      configuracion >> nAtributos;

      while(nAtributos > 0 ){ // Guardamos los atributos
        //Crear un nuevo atributo y añadirle los valores y guardalos en la lista.

        configuracion >> atributo;
        configuracion >> tipo;



        if (tipo == "Nom") { // Si es de tipo Num hay que guardar los valores
          configuracion >> valor;
         Atributo* a1 = new Atributo(atributo,tipo,valor);
         listaAtributo.push_back(a1);
        }
        else {
          list<string> valores; //TODO lista null
          Atributo* a1 = new Atributo(atributo,tipo);
          listaAtributo.push_back(a1);
        }

        nAtributos--;
      }
      configuracion >> objetivo;
      if (objetivo == "OBJETIVO"){
        configuracion >> valorObjetivo;

        objetivo = valorObjetivo;
        globalObjetivo= objetivo;
        configuracion >> prioridad;
        if (prioridad == "PRIORIDADES-REGLAS") {
            configuracion >> numeroReglas;
            nReglas=numeroReglas;
            while(numeroReglas > 0 ){ // Guardamos los atributos
              //Crear un nuevo atributo y añadirle los valores y guardalos en la lista.
              configuracion >> valorPrioridad;
              listaprioridades.push_back(valorPrioridad);
              numeroReglas--;
            }

        }else {
          printf ("Error leyendo la configuracion (PRIORIDADES-REGLAS) \n");
          exit(EXIT_FAILURE);
        }



      }else {
        printf ("Error leyendo la configuracion (OBJETIVOS) \n");
        exit(EXIT_FAILURE);
      }


  }else {
    printf ("Error leyendo la configuracion (ATRIBUTOS) \n");
    exit(EXIT_FAILURE);
  }


}
list<int> LectorConfiguracion::getListaprioridades(){

  return listaprioridades;
}
string LectorConfiguracion::getObjetivo(){
  return objetivo;
}
list<Atributo*> LectorConfiguracion::getAtributos(){
  return listaAtributo;
}

LectorBH::LectorBH() {
nHechos=0;
}
list<Hecho*> LectorBH::getListaHechos(){

  return listaHechos;
}

void LectorBH::leer(string file) {
  ifstream baseHechos(file.c_str(), ifstream::in);
  int numeroHechos;
  string atributo;
  string op;
  string valor;
  //list<Hecho*> listaux;
  baseHechos >> numeroHechos;
  nHechos=numeroHechos;

  while(numeroHechos > 0){  // Leemos los hechos del archivo
    baseHechos >> atributo;
    baseHechos >> op;
    baseHechos >> valor;
    Hecho* h = new Hecho(atributo,valor,op);
    listaHechos.push_back(h);
    numeroHechos--;
  }

  fs << "----Base de Hechos Inicial----"<< endl;

for(std::list<Hecho*>::iterator list_iter = listaHechos.begin();
     list_iter != listaHechos.end(); list_iter++){
       Hecho* aux = *list_iter;
      fs << aux->getNombre() << " " <<aux->getOp() << " "<< aux->getValor() << endl;


     }

     fs << "-----Ejecutando----"<< endl;


}

void LectorBH::ejecutar(LectorBC* bc, LectorConfiguracion* lc) { //Ejecucion del motor de inferencia

  fs<< "Dominio: "<<bc->getDominio()<<endl;
  fs<< "Objetivo: "<<lc->getObjetivo()<<endl<<endl;

  bool continuar=true;
  list<Atributo*> lisAtributos = lc->getAtributos();
  list<Regla*> listaR = bc->getListaReglas();
  string obj = lc->getObjetivo();

  // Ya tenemos los hechos iniciales insertados

  if (!(listaR.empty()) && !(listaHechos.empty()) && (continuar)){
     // Tendremos que buscar el conjunto conflicto.

    /* for(std::list<Regla*>::iterator list_iter = listaR.begin(); //TODO BORRAR
        list_iter != listaR.end(); list_iter++){
          Regla* aux = *list_iter;

       }

       for(std::list<Hecho*>::iterator list_iter = listaHechos.begin();
          list_iter != listaHechos.end(); list_iter++){
            Hecho* h = *list_iter;

          }
          */

      funcionConjuntoConflicto(listaR,lisAtributos);

      if(!(ConjuntoConflicto.empty())){ // Si no es vacio resolvemos y aplicamos
      Regla *r = resolver(ConjuntoConflicto); // Escogemos la regla que toca
      listaR.remove(r); // La borramos para no cogerla de nuevo
      for(std::list<Regla*>::iterator list_iter = listaR.begin();
         list_iter != listaR.end(); list_iter++){
           Regla* aux = *list_iter;

        }

      Hecho *h = aplicar(r); //Guardamos la regla en la base de Hechos

      listaHechos.push_back(h); // Nueva base de Hechos

      continuar = comprobarContenida(obj);

    }

     //Aqui acaba el primer conjunto conflicto
    while(!(ConjuntoConflicto.empty()) && !(listaR.empty()) && (continuar)){

        ConjuntoConflicto.clear();
        funcionConjuntoConflicto(listaR,lisAtributos); //Equiparamos

        if(!(ConjuntoConflicto.empty())){ // Si no es vacio resolvemos y aplicamos
        Regla *r = resolver(ConjuntoConflicto); // Escogemos la regla que toca

        listaR.remove(r); // La borramos para no cogerla de nuevo
        for(std::list<Regla*>::iterator list_iter = listaR.begin();
           list_iter != listaR.end(); list_iter++){
             Regla* aux = *list_iter;


          }

        Hecho *h = aplicar(r); //Guardamos la regla en la base de Hechos
        listaHechos.push_back(h); // Nueva base de Hechos

        continuar = comprobarContenida(obj);

      }
    }

  }
   imprimirBaseHechos(lc,bc);
   fs.close();
}

bool LectorBH::comprobarContenida(string objetivo){

  for(std::list<Hecho*>::iterator list_iter2 = listaHechos.begin();
     list_iter2 != listaHechos.end(); list_iter2++){
       Hecho *h2 = *list_iter2;

       if(h2->getNombre() == objetivo) {
         fs<< "¡Se ha llegado al objetivo: "<< globalObjetivo<<"!"<<endl<<endl;
         return false;
       }

     }
     return true;
}

void LectorBH::imprimirBaseHechos(LectorConfiguracion* lc,LectorBC* bc){



  fs<<"-------- IMPRIMIENDO LA BASE DE HECHOS FINAL -------"<<endl;

  for(std::list<Hecho*>::iterator list_iter2 = listaHechos.begin();
     list_iter2 != listaHechos.end(); list_iter2++){ //Recorremos los hechos de la regla

       Hecho *h1 = *list_iter2;
       fs<<  h1->getNombre()<< " " << h1->getOp() << " " << h1->getValor()<<endl ;

       //Falta imprimir objetivo


     }
}

void LectorBH::funcionConjuntoConflicto(list<Regla*> listaR,list<Atributo*> listaA){
  int contador=0;
  int tamano=0;
  int valor1;
  int valor2;
  string tipo1;
  string tipo2;
  for(std::list<Regla*>::iterator list_iter = listaR.begin(); //Lista de reglas
     list_iter != listaR.end(); list_iter++){
       Regla* aux = *list_iter;
       list<Hecho*> listaHaux = aux->getA();
       tamano=listaHaux.size();  //Lista de Hechos de la regla tendremos que comparar estos con la base de hechos


         for(std::list<Hecho*>::iterator list_iter2 = listaHaux.begin();
            list_iter2 != listaHaux.end(); list_iter2++){
               //Recorremos los hechos de la regla
              Hecho *h1 = *list_iter2;


              for(std::list<Hecho*>::iterator list_iter3 = listaHechos.begin();
               list_iter3 != listaHechos.end(); list_iter3++){
                 //Recorremos los Hechos de la base de Hechos

                 Hecho *h2 = *list_iter3;

                 tipo1= comprobarTipo(h1,listaA);
                 tipo2=comprobarTipo(h2,listaA);

                 if((tipo1==tipo2) && (tipo1 == "Nom")){
                 if( (h2->getNombre() == h1->getNombre())  && (h2->getOp()== h1->getOp() ) &&( h2->getValor()== h1->getValor() ) ){
                   contador++;
                      }
               }else if((tipo1==tipo2) && (tipo1 == "NU")&&(h1->getNombre()==h2->getNombre())){ //Si es de tipo NU
                 string ope = h1->getOp();
                 valor1=atoi(h1->getValor().c_str());
                 valor2=atoi(h2->getValor().c_str());

                 if(ope=="<"){
                   if(valor2<valor1)contador++;
                 }
                 else if (ope==">"){
                   if(valor2>valor1)contador++;
                 }
                 else if (ope=="=>"){
                   if(valor2>=valor1)contador++;
                 }
                 else if (ope=="=<"){
                   if(valor2<=valor1)contador++;
                 }
                 else if (ope=="="){
                   if(valor2==valor1)contador++;
                 }

               }
        }
      }

      if(contador == tamano) {
       ConjuntoConflicto.push_back(aux); //Añadimos la regla al conjunto conflicto
    }
    contador=0;

 }

}
string LectorBH::comprobarTipo(Hecho* h2,list<Atributo*>listaA){

  for(std::list<Atributo*>::iterator list_iter = listaA.begin();
   list_iter != listaA.end(); list_iter++){
     Atributo* a =*list_iter;
     string aux = a->getAtributo();
     string tipo = a->getTipo();
     if(aux==h2->getNombre()){
       return tipo;
     }

  }
   return "";
}

Regla* LectorBH::resolver(list<Regla*> listaR){
      Regla* resultado = listaR.front();

  for(std::list<Regla*>::iterator list_iter = listaR.begin(); //Lista de reglas
     list_iter != listaR.end(); list_iter++){

       Regla* aux = *list_iter;
       if(aux->getPrioridad()>resultado->getPrioridad()) resultado=aux;

     }
     fs<< "Se resuelve la regla " << resultado->printRegla() << "  - Con prioridad: "<< resultado->getPrioridad()<<endl<<endl;
     fs<< "Se añade a la base de hechos el hecho: " + resultado->getB()->printHecho()<<endl<<endl;

     return resultado;
}

Hecho* LectorBH::aplicar(Regla* r){
  Hecho* resultado=r->getB();
  return resultado;


}


LectorBC::LectorBC() {
nReglas=0;
}

list<Regla*> LectorBC::getListaReglas(){

  return listaReglas;
}
string LectorBC::getDominio(){

  return dominioAplicacion;
}



void LectorBC::leer(string file, LectorConfiguracion* lc) {
  ifstream baseConocimiento(file.c_str(), ifstream::in);
  string dominio;
  int numeroReglas;
  string identificador;
  string si;
  string atributo;
  string op;
  string valor;
  string entonces="";
  int prioridad;
  int aux;
  list<int> listpri;
  list<Hecho*>listaH;


  getline(baseConocimiento, dominio, '\n');
  dominioAplicacion=dominio;
  baseConocimiento >> numeroReglas;
  nReglas= numeroReglas;
  listpri = lc->getListaprioridades();

  for(std::list<int>::iterator list_iter = listpri.begin();
     list_iter != listpri.end(); list_iter++){

      list<Hecho*>listaH;
     baseConocimiento >> identificador;
     baseConocimiento >> si;
     if (si == "Si") {  // Antecedentes
       while(!(entonces == "Entonces")){
       baseConocimiento >> atributo;
       baseConocimiento >> op;
       baseConocimiento >> valor;
       Hecho* h = new Hecho(atributo,valor,op);
       listaH.push_back(h);
       baseConocimiento >> entonces;

      }

      baseConocimiento >> atributo;  // Consecuente
      baseConocimiento >> op;
      baseConocimiento >> valor;
      Hecho* hecho = new Hecho(atributo,valor,op);
      entonces="";
      prioridad = *list_iter;
      Regla* regla = new Regla(identificador,prioridad,listaH,hecho);
      listaReglas.push_back(regla);
      listaH.clear();

}else{
    printf ("Error leyendo la configuracion (Reglas) \n");
    exit(EXIT_FAILURE);
    }
  }

}
