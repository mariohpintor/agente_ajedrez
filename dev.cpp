#include "chess.h"
#include "mcts.h"
#include "nodo.h"
#include <iostream>

const float C = 1.4;


int main(){
    Chess juego;
    juego.estado_inicial();
    //Coordenadas accion = {0,4,4,4};
    //Nodo mi_nodo(juego,C, accion,-1,juego.tablero,nullptr);

    MCTS MCTS(juego,C,2);  // Crear una instancia de MCTS y pasarle Chess y Nodo

    // Realizar la búsqueda
    MCTS.busquedas(juego.tablero);

    for (int i = 0; i < MCTS.probs_acciones.size();i++){
        std::cout << MCTS.probs_acciones.at(i) << std::endl; 
    }


    return 0;
}