#include "chess.h"
#include "mcts.h"
#include <iostream>


int main(){
    Chess juego;
    Coordenadas accion = {0,0,0,0};
    Nodo nodo(juego,0, 0, accion);
    nodo.estado_inicial();
    return 0;
}