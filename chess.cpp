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
    /*
    columnas[0] = "A"; columnas[1] = "B"; columnas[2] = "C";
    columnas[3] = "D"; columnas[4] = "E"; columnas[5] = "F";
    columnas[6] = "G"; columnas[7] = "H";*/
    columnas = "ABCDEFGH";
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
          rey_blanco[0]= 7;
          rey_blanco[1] = 4;
          rey_negro[0]= 0;
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
       
       if (accion.x < 8){
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
          
       } else{ enroque(accion);}
}

   int Chess::minimo(int a, int b) {
    if (a < b){return a;} else {return b;}
   }
   
   void Chess::diagonales(int jugador,int i, int j,std::vector<Coordenadas>& movimientos){
     // derecha arriba
   for (int k = 1; k <= minimo(7-j,i);k++){
     if( tablero[i-k][j+k][1] == 0){
        movimientos.push_back({i,j,i-k,j+k});
     } else if(tablero[i-k][j+k][1] == -jugador) {
         movimientos.push_back({i,j,i-k,j+k});
         break;
     }
     else{break;}}
   // izquierda arriba
   for (int k = 1; k <= minimo(j,i);k++){
       if(tablero[i-k][j-k][1] == 0){
       movimientos.push_back({i,j,i-k,j-k});
       } else if (tablero[i-k][j-k][1] == -jugador) 
          {
           movimientos.push_back({i,j,i-k,j-k});
           break;
           }
           else{break;}
    }
   // izquierda abajo 
   for (int k = 1; k <= minimo(j,7-i);k++){
     if(tablero[i+k][j-k][1] == 0 ){
        movimientos.push_back({i,j,i+k,j-k});
     } else if(tablero[i+k][j-k][1] == -jugador){
        movimientos.push_back({i,j,i+k,j-k});
        break;
     } else
     {break;}}
   // derecha abajo
   for (int k = 1; k <= minimo(7-j,7-i);k++){
     if(tablero[i+k][j+k][1]==0){
        movimientos.push_back({i,j,i+k,j+k});
     } else if(tablero[i+k][j+k][1]==-jugador){
         movimientos.push_back({i,j,i+k,j+k});
         break;
     } else
     {break;}}
                       
    }

    void Chess::rectas(int jugador,int i, int j,std::vector<Coordenadas>& movimientos){
   // arriba
   for(int k=1; k <= i;k++){
      if(tablero[i-k][j][1] == 0 ){
        movimientos.push_back({i,j,i-k,j});
      }else if(tablero[i-k][j][1] == -jugador){
        movimientos.push_back({i,j,i-k,j});
        break;
    } else
      {break;}
   }
   // derecha
   for(int k=1; k <= 7-j;k++){
      if(tablero[i][j+k][1] == 0 ){
        movimientos.push_back({i,j,i,j+k});
      }else if(tablero[i][j+k][1] == -jugador){
        movimientos.push_back({i,j,i,j+k});
        break;
    } else {break;}
   } 
   // izquierda
   for(int k=1; k <=j;k++){
      if(tablero[i][j-k][1] == 0 ){
        movimientos.push_back({i,j,i,j-k});
      }else if(tablero[i][j-k][1] == -jugador){
        movimientos.push_back({i,j,i,j-k});
        break;
      }else{break;}
   } 
   // abajo
   for(int k=1; k <=7-i;k++){
      if(tablero[i+k][j][1]==0){
        movimientos.push_back({i,j,i+k,j});
      }else if(tablero[i+k][j][1]==-jugador){
        movimientos.push_back({i,j,i+k,j});
        break;
    }else 
      {break;}
  }
   
}
/*
void obtener_rey_openente(int jugador){
    if (jugador == -1){
        rey[0] = rey_negro[0];
        rey[1] = rey_negro[1];
    }else{
        rey[0] = rey_blanco[0];
        rey[1] = rey_blanco[1];
    }
}*/

   // obtener movimientos validos
   std::vector<Coordenadas>  Chess::movimientos_validos(int jugador) {
       // regresar una lista de los movimientos dado el estado actual
       // ver cada pieza que puede moverse en el  tablero actual y ver a donde puede moverse
       // condiciones
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
                       // AFIL
                        //if (clavada(i,j)){ diagonales(jugador,i,j,movimientos);}
                       diagonales(jugador,i,j,movimientos);
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
                      rectas(jugador,i,j,movimientos);
                      continue;
                    case 5:
                    // reina
                     // parte de afil
                      diagonales(jugador,i,j,movimientos);
                     // parte de torre
                      rectas(jugador,i,j,movimientos);
                     continue;
                    case 6:
                     // rey 
                     int pasos[8][2] = {{i-1,j},{i-1,j+1},{i,j-1},{i+1,j+1}
                                       ,{i+1,j},{i+1,j-1},{i,j+1},{i-1,j-1}};
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

   void Chess::checar_enroque(int jugador,vector<Coordenadas>& movimientos){
     // esta funcion regresa el tipo de enroque disponible
      int row;
      row = jugador == -1 ?7:0;
      info_enroque = 1;
      movimientos2 = movimientos_validos(-jugador);
     // Verifiquemos las condiciones
     // hay espacio y las piezas estan en su lugar?
        if(tablero[row][4][2] == 6){
           // enroque largo
           if (tablero[row][0][2] == 4 && tablero[row][1][2]==0 && tablero[row][2][2]==0 && tablero[row][3][2]==0){
              for(int i=0; i< 5; i++){
                  for ( Coordenadas move: movimientos2){
                    if(row==move.z && i== move.w){
                    info_enroque = 0;
                    break;
                   }
             }}}else{info_enroque = 0;}

            if(info_enroque){
                cout << "Enroque largo"<<endl;
                movimientos.push_back({8,jugador,0,0});}
          info_enroque = 1;
          // enroque corto
          if (tablero[row][7][2] == 4 && tablero[row][5][2]==0 && tablero[row][6][2]==0){
            for(int i=5; i< 8; i++){
                  for ( Coordenadas move: movimientos2){
                    if(row==move.z && i== move.w){
                    info_enroque = 0;
                    break;
                   }
                }}}else{info_enroque = 0;}
         if(info_enroque){
            cout << "Enroque corto"<<endl;
            movimientos.push_back({9,jugador,0,0});}
       }
    }

   void Chess::enroque(Coordenadas accion) { 
     // intercambiar rey con torre
     // esta funcion ejecuta el tipo de enroque
      int row;
      row = accion.y == -1 ? 7: 0;
         switch (accion.x){
        // enroque largo
          case 8:
            tablero[row][2][2]= 6;
            tablero[row][2][1]= accion.y;
            tablero[row][3][2]= 4;
            tablero[row][3][1]= accion.y;

            tablero[row][4][2] = 0;
            tablero[row][4][1] = 0;
            tablero[row][0][1] = 0;
            tablero[row][0][2] = 0;

            if (accion.y == -1){
                rey_blanco[0] = row;
                rey_blanco[1] = 2;
            }else{
                rey_negro[0] = row;
                rey_negro[1] = 2;
            }

           break;
        // enroque corto
          case 9:
            tablero[row][6][2]= 6;
            tablero[row][6][1]= accion.y;
            tablero[row][5][2]= 4;
            tablero[row][5][1]= accion.y;

            tablero[row][4][1] = 0;
            tablero[row][4][2] = 0;
            tablero[row][7][1] = 0;
            tablero[row][7][2] = 0;

            if (accion.y == -1){
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

       if(accion.x < 8){

       notation = columnas[accion.y];
       notation+= to_string(8-accion.x);
       notation+="-";
       notation+= columnas[accion.w];
       notation += to_string(8-accion.z);
       return notation;}
       else if(accion.x == 8){
         return "O-O-O";
       } else {
         return "O-O";
       }
   }

   Coordenadas Chess::notacion_a_movimiento(std::string move){
       int i;
       Coordenadas accion;
       accion.x = 8 - (move[1] - '0');
       for ( i = 0; i< 8;i++){
         if(move[0] == columnas[i]){break;}
       }
       accion.y = i;
       for ( i = 0; i< 8;i++){
         if(move[3] == columnas[i]){break;}
       }
       accion.z = 8 - (move[4] - '0');
       accion.w = i;

       return accion;

   }

   void Chess::mostrar_movimientos(vector<Coordenadas>& movimientos) {
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
    
    // aplicar despues de movimientos_validos
    void Chess::clavadas(int jugador,std::vector<Coordenadas>& movimientos){
    // Si una pieza esta clavada no puede moverse
    // entonces omitimos el calculo de sus movimientos validos
    // Afil , Torre y Reina son los que pueden clavar
    // en la trayectoria debe estar Amenaza Pieza Rey
    int color, pieza;
    //vector<int> pos;
    piezas_clavadas.clear();
    for (int i = 0; i < 8; i++){
           for(int j = 0; j < 8; j++ ){
              if (tablero[i][j][1] == jugador){
                    /*Podemos quitar la pieza victima del jugador del tablero con*/
                  
                  color = tablero[i][j][1];
                  pieza = tablero[i][j][2];
                  tablero[i][j][1] = 0;
                  tablero[i][j][2] = 0;
                  // y ver si existe jaque
                  if(checar_jaque(jugador)){
                    piezas_clavadas.push_back(i);
                    piezas_clavadas.push_back(j);
                  }
                  // regresar pieza
                  tablero[i][j][1] = color;
                  tablero[i][j][2] = pieza;
              }
           }}

        cout << "#clavadas: "<< piezas_clavadas.size()/2<< endl;
        for(int i = 0; i < piezas_clavadas.size() ;i+=2){
            cout <<piezas_clavadas[i]<<","<< piezas_clavadas[i+1]<< endl;
        }

        if(piezas_clavadas.size()>0){
            // quitar piezas clavadas de movimientos, SOLO DEJAR AQUELLA QUE CAPTURA LA AMENAZA
            for (int j =  movimientos.size() -1; j > -1 ;j--){
                for (int i=0; i < piezas_clavadas.size();i+=2){
                   if(movimientos[j].x == piezas_clavadas[i] && movimientos[j].y == piezas_clavadas[i+1]){
                      
                      /*  */
                      // movimientos[j].z == jaqueadora[0] && movimientos[j].w == jaqueadora[1]
                      if(tablero[movimientos[j].z][movimientos[j].w][2] == 2 || tablero[movimientos[j].z][movimientos[j].w][2] == 4 ||
                          tablero[movimientos[j].z][movimientos[j].w][2] == 5)
                        {continue;}
                     else{movimientos.erase(movimientos.begin()+j);}
                   } 
                }
            }
        }

     }
   // checar quien gana
   bool Chess::checar_jaque(int jugador) {
      int rey[2];
      if(jugador == 1){
          rey[0] = rey_negro[0];
          rey[1] = rey_negro[1];}
      else{rey[0] = rey_blanco[0];
          rey[1] = rey_blanco[1];}
      movimientos2.clear();
      movimientos2 = movimientos_validos(-1*jugador);
      for (const auto& elemento : movimientos2) {
           //cout << elemento.z<< elemento.w << "rey: ["<< rey[0]<<","<< rey[1]<<"]"<<endl;
           // PODEMOS OBTENER QUE PIEZA ESTA DANDO JAQUE
          if(elemento.z ==rey[0] && elemento.w == rey[1]){
            //jaqueadora[0] = elemento.x;
            //jaqueadora[1] = elemento.y;
            return true;
          }
     }
     return false;
   }

   void Chess::movimientos_validos_jaque(int jugador) {
       //movimientos.clear();
       int pieza[2];
       vector<Coordenadas> moves;
       Coordenadas accion_inversa; 
       moves = movimientos_validos(jugador);
       for (const auto& elemento : moves){
            accion_inversa.x  = elemento.z;
            accion_inversa.y = elemento.w;
            accion_inversa.z = elemento.x;
            accion_inversa.w = elemento.y;
            if(tablero[elemento.z][elemento.w][1] == -jugador){
                pieza[0] = tablero[elemento.z][elemento.w][2];
                pieza[1] = tablero[elemento.z][elemento.w][1];
            }else
               {pieza[0]=0;
                pieza[1]=0;}
           siguiente_estado(elemento); 
           if(!checar_jaque(jugador)){ 
               moves_jaque.push_back(elemento);
           } 
           siguiente_estado(accion_inversa);
           tablero[elemento.z][elemento.w][1] = pieza[1];
           tablero[elemento.z][elemento.w][2] = pieza[0];
           
       }
   }

   bool Chess::checar_jaque_mate() {
     if(moves_jaque.size()<1){ return true;}
    return false;
   }
   // obtener valor y terminar
   int Chess::valor_terminar(int jugador) {
    if (checar_jaque_mate()){return 1;} // gano último jugador
    else if(movimientos_validos(jugador).size() < 1){ return 0;} // ahogado
    else {return 0;} // empate
    return 0;
   }
   // obtener oponente
   int Chess::obtener_oponente(int jugador) {
       return -1*jugador;
   }

