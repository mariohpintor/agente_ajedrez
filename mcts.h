#ifndef MCTS_H  // Guardia de inclusión
#define MCTS_H

#include "chess.h" 
#include "nodo.h"


class MCTS{
    private:
    Chess& chess;  // Referencia a Chess
    Nodo& nodo;    // Referencia a Nodo

    public:
      // Constructor
      MCTS(Chess& chessInstance, Nodo& nodoInstance);
      int argumentos[2];
      // Métodos
      void busquedas();
};

#endif  // Fin de la guardia de inclusión