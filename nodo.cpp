#include "nodo.h"
#include <iostream>
#include <vector>
#include <cmath>

    // Constructor que recibe una referencia a Chess
    Nodo::Nodo(Chess& chessInstance, int args, int parent, Coordenadas accion_tomada,int jugador) : chess(chessInstance) {
        // Inicializar el nodo con la instancia de Chess
       std::vector <int> hijos; // esta bien definida ? 
       int visit_count = 0;
       int value_sum = 0; 
       std::vector<Coordenadas> movimientos_expandibles = chess.movimientos_validos(jugador);
    }

    // Métodos 
    bool completamente_expandido(){
        return chess.movimientos_validos(jugador)< 0 && hijos.size > 0;
    }

    int seleccion(){
        int mejor_hijo;
        float mejor_ucb = -10000;

        for(int i; i < hijos.size(); i++){
            float ucb = obtener_ucb(hijos[i]);
            if( ucb > mejor_ucb){
                mejor_hijo = i;
                mejor_ucb = ucb;
            }
        }
        return mejor_hijo;
    }
     // hijo debe ser un nodo REVISAR
    float obtener_ucb(Nodo hijo){
        // normalizar y tomar en cuenta que el hijo es oponente de padre y viceversa
        float q_valor = hijo.value_sum / hijo.visit_count;
        return q_valor + args*sqrt(log(hijo.visit_count)/hijo.visit_count);
    }


