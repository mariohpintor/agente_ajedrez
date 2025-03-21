#include "chess.h"
#include <iostream>
using namespace std;

// Constructor
Chess::Chess() {
    // Inicializar figuras
    //figuras_blancas[0] = "♙"; figuras_blancas[1] = "♗";
    //figuras_blancas[2] = "♘"; figuras_blancas[3] = "♖";
    //figuras_blancas[4] = "♕"; figuras_blancas[5] = "♔";

    figuras_negras[0] = "♟"; figuras_negras[1] = "♝";
    figuras_negras[2] = "♞"; figuras_negras[3] = "♜";
    figuras_negras[4] = "♛"; figuras_negras[5] = "♚";

    // Inicializar nombres de piezas
    piezas[0] = "VACIO"; piezas[1] = "PEON";
    piezas[2] = "ALFIL"; piezas[3] = "CABALLO";
    piezas[4] = "TORRE"; piezas[5] = "REINA";
    piezas[6] = "REY";

    columnas[0] = "A"; columnas[1] = "B"; columnas[2] = "C";
    columnas[3] = "D"; columnas[4] = "E"; columnas[5] = "F";
    columnas[6] = "G"; columnas[7] = "H";
}
  void Chess::mostrarPiezas() {
        for (int i = 0; i < 7; i++) {
            cout << piezas[i] << " : " << i << endl;
        }
    }

  void Chess::estado_inicial() {
     for (int i = 0; i < 8; i++){
       for (int j = 0; j< 8; j++){
           // color de casillas
           if (i%2 == 0){ 
               if(j%2 == 0){ tablero[i][j][0]= -1;} // -1 casilla blanca
               else{tablero[i][j][0]= 1;}// 1 casilla negra
              }
           else{ 
               if((j+1)%2 == 0){ tablero[i][j][0]= -1;} 
               else{tablero[i][j][0]= 1;}
              } 
           // color de piezas y peones
           if(i == 1 || i == 0){
               tablero[i][j][1] = 1; // piezas negras
               tablero[i][j][2] = 1;}
           else if(i == 6 || i == 7){
               tablero[i][j][1] = -1; // piezas blancas
               tablero[i][j][2] = 1;}
            else{
                tablero[i][j][1] = 0;
                tablero[i][j][2] = 0;}
            
          // tipo de piezas
          // torres
          tablero[0][0][2] = 4;
          tablero[0][7][2] = 4;
          tablero[7][0][2] = 4;
          tablero[7][7][2] = 4;
          // caballos
          tablero[0][1][2] = 3;
          tablero[0][6][2] = 3;
          tablero[7][1][2] = 3;
          tablero[7][6][2] = 3;
          // alfiles
          tablero[0][2][2] = 2;
          tablero[0][5][2] = 2;
          tablero[7][2][2] = 2;
          tablero[7][5][2] = 2;
          // reinas
          tablero[0][3][2] = 5;
          tablero[7][3][2] = 5;
          //reyes
          tablero[0][4][2] = 6;
          tablero[7][4][2] = 6;
          rey_blanco[0]= 0;
          rey_blanco[1] = 4;
          rey_negro[0]= 7;
          rey_negro[1] = 4;
            //cout <<"[" <<tablero[i][j][0] << ","<< tablero[i][j][1] <<","<< tablero[i][j][2] << "]"<<" ";
       }
        //cout << endl;
     }
  }

  void Chess::mostrar_estado() {
      for (int i = 0; i < 8; i++){
       for (int j = 0; j< 8; j++){
            cout <<"[" <<tablero[i][j][0] << ","<< tablero[i][j][1] <<","<< tablero[i][j][2] << "]"<<" ";
       }
        cout << endl;
     }
  }
   // obtener siguiente estado
   void Chess::siguiente_estado(Coordenadas accion) {
       // una pieza cambia su posición
       // accion = [x_inicio,y_inicio,x_destino,y_destino]

       if (accion.x > 7){
          if (accion.x == 8){enroque(1);} else {enroque(2);}
       } else{
        //guardar posición de reyes
         if(tablero[accion.x][accion.y][2] == 6){
          if (tablero[accion.x][accion.y][1] == -1) {
            rey_blanco[0] = accion.z;
            rey_blanco[1] = accion.w;
           } else {
            rey_negro[0] = accion.z;
            rey_negro[1] = accion.w;
           }
         }

       tablero[accion.z][accion.w][1] = tablero[accion.x][accion.y][1]; // jugador
       tablero[accion.z][accion.w][2] = tablero[accion.x][accion.y][2]; // pieza
       tablero[accion.x][accion.y][1] = 0; // vaciar casilla antigua
       tablero[accion.x][accion.y][2] = 0;
       }
       
   }

   int Chess::minimo(int a, int b) {
    if (a < b){return a;} else {return b;}
   }
   // obtener movimientos validos
   std::vector<Coordenadas>  Chess::movimientos_validos(int jugador) {
       // regresar una lista de los movimientos dado el estado actual
       // ver cada pieza que puede moverse en el  tablero actual y ver a donde puede moverse
       // condiciones
       // hay clavada? 
       int row;
        if(jugador == -1){row = 7;}
          else {row = 0;}
       if (tablero[row][4][2] == 6){checar_enroque(jugador);}

       vector<Coordenadas> movimientos;
       for (int i = 0; i < 8; i++){
           for(int j = 0; j < 8; j++ ){
              
               if (tablero[i][j][1] == jugador){
                   switch(tablero[i][j][2]) {
                    case 1:
                      // peon 
                      // Son los únicos que solo pueden hacia enfrente
                      if (jugador == -1){ // caso blanco
                           if(tablero[i-1][j][2]==0){
                           movimientos.push_back({i,j,i-1,j});}//j = j-1
                           //primer movimiento peon
                           if (i == 6 && tablero[i-2][j][2]==0){movimientos.push_back({i,j,i-2,j});}
                           // captura
                           if (tablero[i-1][j-1][1]==1){movimientos.push_back({i,j,i-1,j-1});}
                           if (tablero[i-1][j+1][1]==1){movimientos.push_back({i,j,i-1,j+1});}
                        } else{// caso negro
                            if(tablero[i+1][j][2]==0){
                            movimientos.push_back({i,j,i+1,j});}//j = j-1
                            //primer movimiento peon
                            if (i == 1 && tablero[i+2][j][2]==0){movimientos.push_back({i,j,i+2,j});}
                            // captura
                            if (tablero[i+1][j+1][1]==-1){movimientos.push_back({i,j,i+1,j+1});}
                            if (tablero[i+1][j-1][1]==-1){movimientos.push_back({i,j,i+1,j-1});}
                        }
                      continue;
                    case 2:
                       // afil
                        // derecha arriba
                       for (int k = 1; k <= minimo(7-j,i);k++){
                         if( tablero[i-k][j+k][1]!=jugador){
                            movimientos.push_back({i,j,i-k,j+k});
                         } else{break;}}
                       // izquierda arriba
                       for (int k = 1; k <= minimo(j,i);k++){
                         if(tablero[i-k][j-k][1]!=jugador){
                            movimientos.push_back({i,j,i-k,j-k});
                         } else{break;}}
                       // izquierda abajo
                       for (int k = 1; k <= minimo(j,7-i);k++){
                         if(tablero[i+k][j-k][1]!=jugador){
                            movimientos.push_back({i,j,i+k,j-k});
                         } else{break;}}
                       // derecha abajo
                       for (int k = 1; k <= minimo(7-j,7-i);k++){
                         if(tablero[i+k][j+k][1]!=jugador){
                            movimientos.push_back({i,j,i+k,j+k});
                         } else{break;}}
                       
                       continue;
                    case 3:{
                       // caballo
                       int saltos[8][2] = {{i-2,j+1},{i-2,j-1},{i+2,j-1},{i+2,j+1},{i-1,j+2},{i-1,j-2},{i+1,j+2},{i+1,j-2}};
                       for (int k = 0; k < 8;k++){
                         if (-1 < saltos[k][0] && saltos[k][0]< 8 && -1 < saltos[k][1] && saltos[k][1]< 8 && tablero[saltos[k][0]][saltos[k][1]][1]!=jugador)
                         { 
                           movimientos.push_back({i,j,saltos[k][0],saltos[k][1]});}
                       }}
                       continue;
                    case 4:
                      // torre
                       // arriba
                       for(int k=1; k <= i;k++){
                          if(tablero[i-k][j][1]!=jugador){
                            movimientos.push_back({i,j,i-k,j});
                          }else{break;}
                       }
                       // derecha
                       for(int k=1; k <= 7-j;k++){
                          if(tablero[i][j+k][1]!=jugador){
                            movimientos.push_back({i,j,i,j+k});
                          }else{break;}
                       } 
                       // izquierda
                       for(int k=1; k <=j;k++){
                          if(tablero[i][j-k][1]!=jugador){
                            movimientos.push_back({i,j,i,j-k});
                          }else{break;}
                       } 
                       // abajo
                       for(int k=1; k <=7-i;k++){
                          if(tablero[i+k][j][1]!=jugador){
                            movimientos.push_back({i,j,i+k,j});
                          }else{break;}
                       } 
                      continue;
                    case 5:
                    // reina
                     // parte de afil
                      // derecha arriba
                       for (int k = 1; k <= minimo(7-j,i);k++){
                         if( tablero[i-k][j+k][1]!=jugador){
                            movimientos.push_back({i,j,i-k,j+k});
                         } else{break;}}
                       // izquierda arriba
                       for (int k = 1; k <= minimo(j,i);k++){
                         if(tablero[i-k][j-k][1]!=jugador){
                            movimientos.push_back({i,j,i-k,j-k});
                         } else{break;}}
                       // izquierda abajo
                       for (int k = 1; k <= minimo(j,7-i);k++){
                         if(tablero[i+k][j-k][1]!=jugador){
                            movimientos.push_back({i,j,i+k,j-k});
                         } else{break;}}
                       // derecha abajo
                       for (int k = 1; k <= minimo(7-j,7-i);k++){
                         if(tablero[i+k][j+k][1]!=jugador){
                            movimientos.push_back({i,j,i+k,j+k});
                         } else{break;}}
                     // parte de torre
                      // arriba
                       for(int k=1; k <= i;k++){
                          if(tablero[i-k][j][1]!=jugador){
                            movimientos.push_back({i,j,i-k,j});
                          }else{break;}
                       }
                       // derecha
                       for(int k=1; k <= 7-j;k++){
                          if(tablero[i][j+k][1]!=jugador){
                            movimientos.push_back({i,j,i,j+k});
                          }else{break;}
                       } 
                       // izquierda
                       for(int k=1; k <=j;k++){
                          if(tablero[i][j-k][1]!=jugador){
                            movimientos.push_back({i,j,i,j-k});
                          }else{break;}
                       } 
                       // abajo
                       for(int k=1; k <=7-i;k++){
                          if(tablero[i+k][j][1]!=jugador){
                            movimientos.push_back({i,j,i+k,j});
                          }else{break;}
                       } 
                     continue;
                    case 6:
                     // rey 
                     int pasos[8][2] = {{i-1,j},{i-1,j+1},{i,j-1},{i+1,j+1}
                                       ,{i+1,j},{i+1,j-1},{i,j-1},{i-1,j-1}};
                     for (int k=0; k<8 ;k++){
                         if(-1< pasos[k][0] && pasos[k][0]<8 && -1< pasos[k][1] && pasos[k][1]<8 && tablero[pasos[k][0]][pasos[k][1]][1]!=jugador)
                         {movimientos.push_back({i,j,pasos[k][0],pasos[k][1]});}
                     }
  
                     continue;
                     }
                   }
               }
       }

       return movimientos;
   }

   void Chess::checar_enroque(int jugador){
     // esta funcion regresa el tipo de enroque disponible
     //info_enroque = {8,1,2,0} primer num de diferenciacion, .y = 1 largo, .z = 2 corto, .w = jugador
      info_enroque.x = 8;
      info_enroque.w = jugador;
      int row;
      if(jugador == -1){row = 7;}
      else {row = 0;}
     // Verifiquemos las condiciones
     // hay espacio y las piezas estan en su lugar?
        if(tablero[row][4][2] == 6){
           // enroque largo
           if (tablero[row][0][2] == 4 && tablero[row][1][2]==0 && tablero[row][2][2]==0 && tablero[row][3][2]==0){
              info_enroque.y = 1;
              movimientos.push_back({8,1,1,1});
            } else{ info_enroque.y = 0 ;}
          // enroque corto
          if (tablero[row][7][2] == 4 && tablero[row][5][2]==0 && tablero[row][6][2]==0){
             info_enroque.z = 2;
             movimientos.push_back({9,2,2,2});
            } else{ info_enroque.z = 0;}
       }

       // el espacio esta bajo ataque?

    }

   void Chess::enroque(int tipo_enroque) { 
     // intercambiar rey con torre
     // esta funcion ejecuta el tipo de enroque
      int row;
      if(info_enroque.w == -1){row = 7;}
      else {row = 0;}
         switch (tipo_enroque){
        // enroque largo
          case 1:
            tablero[row][2][2]= 6;
            tablero[row][2][1]= info_enroque.w;
            tablero[row][3][2]= 4;
            tablero[row][3][1]= info_enroque.w;

            tablero[row][4][2] = 0;
            tablero[row][4][1] = 0;
            tablero[row][0][1] = 0;
            tablero[row][0][2] = 0;

            if (info_enroque.w == -1){
                rey_blanco[0] = row;
                rey_blanco[1] = 2;
            }else{
                rey_negro[0] = row;
                rey_negro[1] = 2;
            }

           break;
        // enroque corto
          case 2:
            tablero[row][6][2]= 6;
            tablero[row][6][1]= info_enroque.w;
            tablero[row][5][2]= 4;
            tablero[row][5][1]= info_enroque.w;

            tablero[row][4][1] = 0;
            tablero[row][4][2] = 0;
            tablero[row][7][1] = 0;
            tablero[row][7][2] = 0;

            if (info_enroque.w == -1){
                rey_blanco[0] = row;
                rey_blanco[1] = 6;
            }else{
                rey_negro[0] = row;
                rey_negro[1] = 6;
            }

           break;
     }

   }

   std::string Chess::movimiento_a_notacion(Coordenadas accion){
       std::string notation;
       notation = columnas[accion.y];
       notation+= to_string(8-accion.x);
       notation+="-";
       notation+= columnas[accion.w];
       notation += to_string(8-accion.z);
       return notation;
   }

   void Chess::mostrar_movimientos(vector<Coordenadas> movimientos) {
       cout << "Movimientos: "<< endl;
       int i = 0;
        for (const auto& elemento : movimientos) {
        
        std::cout << "[" << elemento.x << ","
                  << elemento.y << ","
                  << elemento.z << ","
                  << elemento.w << "] | ";
          
        std::cout << movimiento_a_notacion(elemento) <<" | "<< i <<std::endl;
        i++;
     }
   }


   void Chess::visualizar_tablero() {
    string COLOR_PIEZA;
    string COLOR_CELDA;
    for (int i = 0; i < 8; i++){
       for (int j = 0; j< 8; j++){

           COLOR_PIEZA = tablero[i][j][1]==-1 ? TEXTO_BLANCO: TEXTO_NEGRO;
           COLOR_CELDA = tablero[i][j][0]==-1 ? AZUL_CLARO : AZUL_OSCURO;
           if (tablero[i][j][2] == 0 ){
               cout << COLOR_CELDA <<" "<<" "<<" " << RESET;
           }else {
            cout << COLOR_CELDA << COLOR_PIEZA << " "<< figuras_negras[tablero[i][j][2]-1] << " "<< RESET;
           }
         } 
         cout << endl;  
      }
    }
   // checar quien gana
   bool Chess::checar_jaque(int jugador) {
    /*dado el estado ver si dentro de los movimientos validos 
     la posición del rey esta ahi
     si jugador ha hecho su jugada 
      ver si el rey de -jugador esta en jaque*/
      int rey[2];
      if(jugador == 1){
          rey[0] = rey_negro[0];
          rey[1]= rey_negro[1];}
      else{rey[0] = rey_blanco[0];
          rey[1]= rey_blanco[1];}
      movimientos.clear();
      movimientos = movimientos_validos(-1*jugador);
      for (const auto& elemento : movimientos) {
          if(elemento.z ==rey[0] && elemento.w == rey[1]){
            cout << "Posición rey: ["<< rey[0]<<","<< rey[1]<<"]"<<endl;
            return true;
          }else{return false;}
     }
     return false;
   }

   void Chess::movimientos_validos_jaque(int jugador) {
       //movimientos.clear();
       vector<Coordenadas> moves;
       Coordenadas accion_inversa; 
       moves = movimientos_validos(jugador);
       for (const auto& elemento : moves){
           siguiente_estado(elemento);
           if(checar_jaque(jugador)){ 
             accion_inversa.x  = elemento.z;
             accion_inversa.y = elemento.w;
             accion_inversa.z = elemento.x;
             accion_inversa.w = elemento.y; // revertir accion 
             siguiente_estado(accion_inversa);
           } else{
              moves_jaque.push_back(elemento);
           }
       }
   }

   bool Chess::checar_jaque_mate(int jugador) {
     if(moves_jaque.size()<1){ return true;}
     else{ return false;} 
    return false;
   }
   // obtener valor y terminar
   int Chess::valor_terminar(int jugador) {
    if (checar_jaque_mate(jugador)){return 1;} // gano jugador
    else{ return -1;} // perdio jugador
    return 0;
   }
   // obtener oponente
   int Chess::obtener_oponente(int jugador) {
       return -1*jugador;
   }

