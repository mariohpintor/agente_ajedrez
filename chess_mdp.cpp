#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

struct Coordenadas {
    int x;
    int y;
    int z;
    int w;
};

class Chess {        
  public: 
   string figuras_blancas[6] = {"♙","♗","♘","♖","♕","♔"};
   string figuras_negras[6] = {"♟","♝","♞","♜","♛","♚"};
   string piezas[7] = {"VACIO","PEON","ALFIL","CABALLO","TORRE","REINA","REY"};
   int tablero[8][8][3];// color de casilla, color de pieza, , tipo de pieza
   int rey_blanco[2];
   int rey_negro[2]; 
   vector<Coordenadas> movimientos;

  void mostrarPiezas() {
        for (int i = 0; i < 7; i++) {
            cout << piezas[i] << " : " << i << endl;
        }
    }

  void estado_inicial(){
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
            cout <<"[" <<tablero[i][j][0] << ","<< tablero[i][j][1] <<","<< tablero[i][j][2] << "]"<<" ";
       }
        cout << endl;
     }
  }

  void mostrar_estado(){
      for (int i = 0; i < 8; i++){
       for (int j = 0; j< 8; j++){
            cout <<"[" <<tablero[i][j][0] << ","<< tablero[i][j][1] <<","<< tablero[i][j][2] << "]"<<" ";
       }
        cout << endl;
     }
  }
   // obtener siguiente estado
   void siguiente_estado(int accion[4]){
       // una pieza cambia su posición
       // accion = [x_inicio,y_inicio,x_destino,y_destino]
       tablero[accion[2]][accion[3]][1] = tablero[accion[0]][accion[1]][1]; // jugador
       tablero[accion[2]][accion[3]][2] = tablero[accion[0]][accion[1]][2]; // pieza
       tablero[accion[0]][accion[1]][1] = 0; // vaciar casilla antigua
       tablero[accion[0]][accion[1]][2] = 0;
   }

   int minimo(int a, int b){
    if (a < b){return a;} else {return b;}
   }
   // obtener movimientos validos
   void  movimientos_validos(int jugador){
       // regresar una lista de los movimientos dado el estado actual
       // ver cada pieza que puede moverse en el  tablero actual y ver a donde puede moverse
       // condiciones
       //hay jaque? clavada? 
       for (int i = 0; i < 8; i++){
           for(int j = 0; j < 8; j++ ){
               //if (!checar_jaque){}
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
                          if(tablero[i][j+k][1]!=jugador){
                            movimientos.push_back({i,j,i,j+k});
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
   }
   // falta enroque

   void mostrar_movimientos(){
       cout << "Movimientos: "<< endl;
       int i = 0;
        for (const auto& elemento : movimientos) {
        std::cout << "(" << elemento.x << ", "
                  << elemento.y << ", "
                  << elemento.z << ", "
                  << elemento.w << ") " << i<<std::endl;
          i++;
     }
   }

   void visualizar_tablero(){
    for (int i = 0; i < 8; i++){
       for (int j = 0; j< 8; j++){
           if (tablero[i][j][1]==-1){
             cout << figuras_blancas[tablero[i][j][2]-1] << " ";
           } else if (tablero[i][j][1]==1){
              cout << figuras_negras[tablero[i][j][2]-1] << " ";
             }
           else{cout << "#" << " ";}
       }
        cout << endl;
     }
   }
   // checar quien gana
   bool checar_jaque(int jugador){
    /*dado el estado ver si dentro de los movimientos validos 
     la posición del rey esta ahi
     si jugador ha hecho su jugada 
      ver si el rey de -jugador esta eb jaque*/
      int rey[2];
      if(-1*jugador == 1){rey[0] = rey_negro[0];
          rey[1]= rey_negro[1];}
      else{rey[0] = rey_blanco[0];
          rey[1]= rey_blanco[1];}
      movimientos.clear();
      movimientos_validos(jugador);
      for (const auto& elemento : movimientos) {
          if(elemento.y ==rey[0] && elemento.w == rey[1]){
            return true;
          }else{return false;}
     }
     return false;
   }

   bool checar_jaque_mate(int jugador){
    /* ver si para algún movimiento del jugador en jaque elimina el jaque
       para cada movimiento de movimientos_validos(jugador) ver si 
       checar_jaque(-jugador,movimientos_jaqueadores)==True */
    return false;
   }
   // obtener valor y terminar
   int valor_terminar(int jugador){
    if (checar_jaque_mate(jugador)){return 1;} // gano jugador
    else{ return -1;} // perdio jugador
    return 0;
   }
   // obtener oponente
   int obtener_oponente(int jugador){
       return -1*jugador;
   }
};

int main(){
    system("Color 0A"); 
    Chess juego; 
    juego.mostrarPiezas();
    cout << "blanco:-1 | negro:1"<< endl;
    juego.estado_inicial();
    int jugador = -1;
     int x,i=0;
    //cout <<"Elige jugador: ";
    //cin >> jugador;
    while(true){
      juego.visualizar_tablero(); // mejor en terminal con fondo blanco y texto negro
      juego.movimientos_validos(jugador);
      //juego.mostrar_movimientos();
      cout <<"Número de movimientos válidos: "<< juego.movimientos.size()<< endl;
      cout << "Número de jugada: "<< i++ << endl;
      cout << "Elige tu movimiento: "; 
      //cin >> x;
      x = rand()% juego.movimientos.size();
      cout << x << endl;
      sleep(1);
      int accion[4] = {juego.movimientos[x].x,juego.movimientos[x].y,juego.movimientos[x].z,juego.movimientos[x].w};
      juego.siguiente_estado(accion);
      juego.movimientos.clear();
      if (juego.checar_jaque(jugador)){
        cout << "Jaque a rey "<< -1*jugador;
        break;}
      jugador = juego.obtener_oponente(jugador);
      
    }
    return 0;
}