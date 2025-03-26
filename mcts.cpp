#include "mcts.h"
#include <iostream>
#include <vector>


    MCTS::MCTS(Chess& chessInstance, Nodo& nodoInstance): chess(chessInstance),nodo(nodoInstance){
           argumentos[0]=3; // número de busquedas
           argumentos[1]=0;
    }

    void MCTS::busquedas(){
        // definir raíz
        // root = nodo();
        for (int i=0;i< argumentos[0]; i++ ){
            std::cout << "mensaje: "<< i <<std::endl;
            // selección
            // expansión
            // simulación
            // retropagación
        }

        // return conteo_visitas
    }