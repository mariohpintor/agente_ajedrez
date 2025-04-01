#include "nodo.h"
#include <iostream>
#include <vector>
#include <cmath>

    // Constructor que recibe una referencia a Chess
    Nodo::Nodo(Chess& chessInstance, Nodo* padre = nullptr, float constante,
               ,Coordenadas accion_tomada,int jugador, 
               int& estado[][8][2]): chess(chessInstance) {

        // Inicializar el nodo con la instancia de Chess
       int jugador = jugador;
       int visit_count = 0;
       int value_sum = 0; 
       std::vector<Coordenadas> movimientos_expandibles = chess.movimientos_validos(jugador);
    }

    // Métodos 
    bool Nodo::completamente_expandido(){
        return chess.movimientos_validos(jugador)< 0 && hijos.size() > 0;
    }

    int Nodo::seleccion(){
        int mejor_hijo;
        float mejor_ucb = -100000;

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
    float Nodo::obtener_ucb(Nodo hijo){
        // normalizar y tomar en cuenta que el hijo es oponente de padre y viceversa
        float q_valor = hijo.value_sum / hijo.visit_count;
        return q_valor + constante*sqrt(log(hijo.visit_count)/hijo.visit_count);
    }

   Nodo* Nodo::expandir(){
          int index_accion = rand()% movimientos_expandibles.size();

          // obtener el estado dada la acción aleatoria
          int estado_hijo[8][8][2] = estado; // estado del padre
          // hacer la funcion siguiente_estado por valor
          siguiente_estado_copy(movimientos_expandibles[index_accion], estado_hijo);
          
          // Crear el nodo hijo con el nuevo estado
          hijo = Nodo(chess, this, constante,
                      movimientos_expandibles[index_accion],-jugador, 
                      estado_hijo);
          // quitar la accion tomada de los movimientos disponibles
          movimientos_expandibles.erase(movimientos_expandibles.begin() + index_accion);

          hijos.push_back(hijo);

          return hijos.back().get();
   }

    int Nodo::simulacion(){
        int valor = chess.valor_terminal(jugador);
    }

    void Nodo::retropropagacion(int valor){}

