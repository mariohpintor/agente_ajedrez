#include "chess.h"
#include "mcts.h"
#include "nodo.h"
#include <iostream>

// COMO USAMOS LA CLASE NODO DENTRO DE LA CLASE MCTS PARA TENER VARIOS NODOS??
int main(){
    Chess juego;
    Coordenadas accion = {0,0,0,0};
    Nodo nodo(juego,0, 0, accion,-1);
    nodo.estado_inicial();
    MCTS MCTS(juego, nodo);  // Crear una instancia de MCTS y pasarle Chess y Nodo

    // Realizar la búsqueda
    MCTS.busquedas();
    return 0;
}