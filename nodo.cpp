#include "nodo.h"
#include <iostream>
#include <vector>
#include <cmath>

    // Constructor que recibe una referencia a Chess
    Nodo::Nodo(Chess& chessInstance,
               float x,Coordenadas y,
              int z, int estado[][8][2], Nodo* parent): chess(chessInstance) {

       visit_count = 0;
       value_sum = 0; 
       constante = x;
       accion_tomada = y; 
       jugador = z;
       movimientos_expandibles = chess.movimientos_validos(jugador);
       padre = parent;
       for (int i=0;i <8; i++){
         for (int j= 0; j < 8 ; j++){
            tablero[i][j][0] = estado[i][j][0]; 
            tablero[i][j][1] = estado[i][j][1]; 
         }
       }
    }

    // Métodos 
    bool Nodo::completamente_expandido(){
        return chess.movimientos_validos(jugador).size() < 1 && hijos.size() > 0;
    }

    int Nodo::seleccion(){
        int mejor_hijo;
        float mejor_ucb = -100000;

        for(int i; i < hijos.size(); i++){
            Nodo* hijo = hijos.at(i);
            float ucb = obtener_ucb(*hijo);
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
          //int estado_hijo[8][8][2] =  tablero; // estado del padre
          // hacer la funcion siguiente_estado por valor
          chess.siguiente_estado_copy(movimientos_expandibles[index_accion], tablero);
          
          // Crear el nodo hijo con el nuevo estado
          Nodo hijo(chess, this, constante,
                      movimientos_expandibles[index_accion],-jugador, 
                       tablero);
          // quitar la accion tomada de los movimientos disponibles
          movimientos_expandibles.erase(movimientos_expandibles.begin() + index_accion);

          hijos.push_back(hijo);

          return hijos.back().get();
   }

    int Nodo::simulacion(){
        int valor = chess.valor_terminar(jugador);
    }

    void Nodo::retropropagacion(int valor){}

