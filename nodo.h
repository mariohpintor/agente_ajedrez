#ifndef NODO_H  // Guardia de inclusión
#define NODO_H

#include "chess.h"  // Incluir la clase Chess

class Nodo {
private:
    Chess& chess;  // Referencia a Chess

public:
    // Constructor
    Nodo(Chess& chessInstance,int args, int parent, Coordenadas accion_tomada,int jugador);  // Usando referencia

    // Métodos
    bool completamente_expandido();

    int seleccion();

    float obtener_ucb();
};


#endif  // Fin de la guardia de inclusión