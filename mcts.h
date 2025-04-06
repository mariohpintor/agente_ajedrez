#ifndef MCTS_H  // Guardia de inclusión
#define MCTS_H

#include "chess.h" 
#include "nodo.h"


class MCTS{
    private:
    Chess& chess;  // Referencia a Chess

    public:
      // Constructor
      float constante;
      int num_busquedas;

      MCTS(Chess& chessInstance, float c,int searches)
      // Métodos
      std::vector<float> busquedas(int estado[][8][2]);
};

#endif  // Fin de la guardia de inclusión