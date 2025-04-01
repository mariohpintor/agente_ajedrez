#ifndef NODO_H  // Guardia de inclusión
#define NODO_H

#include "chess.h"  // Incluir la clase Chess

class Nodo {
private:
    Chess& chess;  // Referencia a Chess
    Nodo* padre;          // Puntero al nodo padre (nullptr si es raíz)
    std::vector<Nodo*> hijos;  // Hijos del nodo

public:
    // Constructor
    Nodo(Chess& chessInstance, Nodo* padre = nullptr,
         float constante,Coordenadas accion_tomada,
         int jugador,int& estado[][8][2]);  // Usando referencia
     int jugador;
     int visit_count = 0;
     int value_sum = 0; 
     std::vector<Coordenadas> movimientos_expandibles;

    // Métodos
    bool completamente_expandido();

    int seleccion();

     float obtener_ucb(Nodo hijo);

    Nodo* expandir();

    int simulacion();

    void retropropagacion(int valor);
};


#endif  // Fin de la guardia de inclusión