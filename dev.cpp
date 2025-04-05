#include "chess.h"
//#include "mcts.h"
#include "nodo.h"
#include <iostream>

const float C = 1.4;

// COMO USAMOS LA CLASE NODO DENTRO DE LA CLASE MCTS PARA TENER VARIOS NODOS??
int main(){
    Chess juego;
    juego.estado_inicial();
    Coordenadas accion = {6,4,4,4};
    Nodo mi_nodo(juego,C, accion,-1,juego.tablero,nullptr);

    //MCTS MCTS(juego, nodo);  // Crear una instancia de MCTS y pasarle Chess y Nodo

    // Realizar la búsqueda
    //MCTS.busquedas();
    return 0;
}