#include "mcts.h"
#include <iostream>
#include <vector>


    MCTS::MCTS(Chess& chessInstance, float c,int searches): chess(chessInstance){
        constante = c;
        num_busquedas = searches;
    }

    void  MCTS::busquedas(int estado[][8][2]){
        // definir raíz
        int valor;
        int jugador = -1;
        Nodo raiz(chess,constante,jugador,chess.tablero); 
        
        for (int i = 0;i < num_busquedas; i++ ){
            while (raiz.completamente_expandido()){
                // selección
                int hijo_seleccionado = raiz.seleccion();   
            }

            valor = chess.valor_terminar(jugador);
            //std::cout << "valor "<< valor<< std::endl;
            valor = -valor;
            
            if (valor!= 1){
                // expansión
                raiz.expandir(raiz.hijos);
                // simulación
                valor = raiz.simulacion();
            }
            // retropagación
            raiz.retropropagacion(valor);
        }

        
        float sum = 0;
        for (int j = 0; j < raiz.hijos.size(); j++){
            sum+= raiz.hijos[j].visit_count;
        }
        for (int j = 0; j < raiz.hijos.size(); j++){
            probs_acciones.push_back(raiz.hijos[j].visit_count/sum);
        }

    }
    