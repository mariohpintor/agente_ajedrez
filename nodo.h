#ifndef NODO_H  // Guardia de inclusión
#define NODO_H

#include "chess.h"  // Incluir la clase Chess

class Nodo {
private:
    Chess& chess;  // Referencia a Chess

public:
    // Constructor
    Nodo(Chess& chessInstance,int args, int parent, Coordenadas accion,int jugador);  // Usando referencia

    // Métodos
    void estado_inicial(); // método provisional
};


#endif  // Fin de la guardia de inclusión