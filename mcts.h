#ifndef MCTS_H  // Guardia de inclusión
#define MCTS_H

#include "Chess.h"  // Incluir la clase Chess


class Nodo {
private:
    Chess& chess;  // Referencia a Chess
    // Chess* chess;  // Puntero a Chess (opcional)

public:
    // Constructor
    Nodo(Chess& chessInstance,int args, int parent, Coordenadas accion);  // Usando referencia
    // Nodo(Chess* chessInstance);  // Usando puntero

    // Métodos
    void estado_inicial();
};

#endif  // Fin de la guardia de inclusión