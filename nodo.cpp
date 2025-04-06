#include "nodo.h"
#include <iostream>
#include <vector>
#include <cmath>
//#include <memory>

    // Constructor que recibe una referencia a Chess
    Nodo::Nodo(Chess& chessInstance,
               float x,int z, int estado[][8][2],Coordenadas y, Nodo* parent): chess(chessInstance) {

       visit_count = 0;
       value_sum = 0; 
       constante = x;
       accion_tomada = y; 
       jugador = z;
       movimientos_expandibles = chess.movimientos_validos(jugador);
       padre = parent;

       copiar_tablero(estado,tablero);
       
    }

    void Nodo::copiar_tablero(int estado1[][8][2], int estado2[][8][2]){
        for (int i=0;i <8; i++){
          for (int j= 0; j < 8 ; j++){
            estado2[i][j][0] = estado1[i][j][0]; 
            estado2[i][j][1] = estado1[i][j][1]; 
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
            //Nodo* hijo = hijos.at(i);
            float ucb = obtener_ucb(hijos.at(i));
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

   void Nodo::expandir(std::vector<Nodo>& hijos){
          int index_accion = rand()% movimientos_expandibles.size();

          // obtener el estado dada la acción aleatoria
          //int estado_hijo[8][8][2] =  tablero; // estado del padre
          // hacer la funcion siguiente_estado por valor
          chess.siguiente_estado_copy(movimientos_expandibles[index_accion], tablero);
          
          // Crear el nodo hijo con el nuevo estado
          Nodo hijo(chess, constante,-jugador, 
                    tablero,movimientos_expandibles[index_accion], this);
          hijos.push_back(hijo);
          // quitar la accion tomada de los movimientos disponibles
          movimientos_expandibles.erase(movimientos_expandibles.begin() + index_accion);

   }

    int Nodo::simulacion(){
        int valor = chess.valor_terminar(jugador);
        valor = -valor; // en los nodos hijos son turno del oponente
        if (valor) {
          return valor;
        }
        //int estado_rollout[8][8][2];
        //copiar_tablero(this->tablero,estado_rollout);
        int rollout_player = 1;
        Chess juego_rollout;
        juego_rollout.estado_arbitrario(this->tablero);


        while (true){
            int index_accion = rand()% movimientos_expandibles.size();
            juego_rollout.siguiente_estado(movimientos_expandibles[index_accion]);
            valor = juego_rollout.valor_terminar(rollout_player);
            
            if (valor){
                if (rollout_player == -1){
                    valor = -valor;
                }
                return valor;
            }
            rollout_player = juego_rollout.obtener_oponente(rollout_player);
        }
       return 0;
    }

    void Nodo::retropropagacion(int valor){
        value_sum += valor;
        visit_count += 1;

        valor = -valor;
        if (padre != nullptr){
            padre->retropropagacion(valor);
        }
    }

