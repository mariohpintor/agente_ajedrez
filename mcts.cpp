#include "mcts.h"
#include <iostream>
#include <vector>

    // Constructor que recibe una referencia a Chess
    Nodo::Nodo(Chess& chessInstance, int args, int parent, Coordenadas accion) : chess(chessInstance) {
        // Inicializar el nodo con la instancia de Chess
       std::vector <int> hijos;
       int visit_count = 0;
       int value_sum = 0; 
    }

    // Métodos para trabajar con Chess
    void  Nodo::estado_inicial() {
        // Ejemplo: Usar la instancia de Chess para realizar un movimiento
        chess.estado_inicial();
        chess.visualizar_tablero();
    }