#ifndef NODO_H  // Guardia de inclusión
#define NODO_H

#include "chess.h"  // Incluir la clase Chess

class Nodo {
//private:
  //  Chess& chess;  // Referencia a Chess
    public:
     Chess& chess;
     Nodo* padre;          // Puntero al nodo padre (nullptr si es raíz)
     int visit_count;
     int value_sum; 
     std::vector<Coordenadas> movimientos_expandibles;
     std::vector<Nodo*> hijos;  // Hijos del nodo
     float constante;
     Coordenadas accion_tomada; 
     int jugador;
     int tablero[8][8][2];


    // Constructor
    Nodo(Chess& chessInstance,
         float x,Coordenadas y,
         int z,int estado[][8][2],Nodo* parent = nullptr);  // Usando referencia



    // Métodos
    bool completamente_expandido();

    int seleccion();

     float obtener_ucb(Nodo hijo);

    Nodo* expandir();

    int simulacion();

    void retropropagacion(int valor);
};


#endif  // Fin de la guardia de inclusión