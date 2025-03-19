#include "mcts.h"
#include <iostream>
#include <vector>


    MCTS::MCTS(Chess& chessInstance, Nodo& nodoInstance): chess(chessInstance),nodo(nodoInstance){
           
    }

    void MCTS::busquedas(){
        // definir raíz
        for (int i=0;i< 3; i++ ){
            std::cout << "mensaje: "<< i <<std::endl;
            // selección
            // expansión
            // simulación
            // retropagación
        }

        // return conteo_visitas
    }