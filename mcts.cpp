#include "mcts.h"
#include <iostream>
#include <vector>


    MCTS::MCTS(Chess& chessInstance, float c,int searches): chess(chessInstance){
        constante = c;
        num_busquedas = searches;
    }

    std::vector<float> MCTS::busquedas(int estado[][8][2]){
        // definir raíz
        int valor;
        Nodo raiz(chess,constante,-1,chess.tablero); // accion y padre args por defecto
        
        for (int i = 0;i < num_busquedas; i++ ){
            while (raiz.completamente_expandido()){
                // selección
                int hijo_seleccionado = raiz.seleccion();   
            }
            valor = chess.valor_terminar();
            valor = -valor;
            
            if (!valor){
                // expansión
                raiz.expandir(raiz.hijos);
                // simulación
                valor = raiz.simulacion();
            }
            // retropagación
            raiz.retropropagacion(valor);
        }

        std::vector<float> probs_acciones;
        float sum = 0;
        for (int j = 0; j < raiz.hijos.size(); j++){
            sum+= raiz.hijos[j].visit_count;
        }
        for (int j = 0; j < raiz.hijos.size(); j++){
            probs_acciones.push_back(raiz.hijos[j].visit_count/sum);
        }

        return probs_acciones;
    }
    