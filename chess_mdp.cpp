#include <iostream>
using namespace std;

class Chess {        
  public: 
   string piezas[7] = {"VACIO","PEON","AFIL","CABALLO","TORRE","REINA","REY"};
   int tablero[8][8][3];// color de casilla, color de pieza, , tipo de pieza


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
               tablero[i][j][1] = -1;
               tablero[i][j][2] = 1;}
           else if(i == 6 || i == 7){
               tablero[i][j][1] = 1;
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

            cout <<"[" <<tablero[i][j][0] << ","<< tablero[i][j][1] <<","<< tablero[i][j][2] << "]"<<" ";
       }
        cout << endl;
     }
  }
     
   // obtener siguiente estado
   void siguiente_estado(accion,jugador){
       // una pieza cambia su posición
       // accion = [x_inicio,y_inicio,x_destino,y_destino]
       // accion mover peon d2 a d4

       //tablero[4][3][1]=tablero[6][3][1];
       //tablero[4][3][1]=tablero[6][3][2];

       //tablero[6][3][1]=0;
       //tablero[6][3][2]=0;
   }

   // obtener movimientos validos
   int movimientos_validos(){
       // regresar una lista de los movimientos dado el estado actual
       int movimientos[];
       // ver cada pieza que puede moverse en el  tablero actual y ver a donde puede moverse
       // condiciones
       //hay jaque? clavada? 
       for (int i = 0; i < 8; i++){
           for(int j = 0; j < 8; j++ ){
               if (tablero[i][j][2]!=0){
                   switch(tablero[i][j][2]) {
                    case 1:
                      // peon
                      if (tablero[i][j][1] == 1){
                          //j = j-1
                          //j = j-2 solo en la posición inicial
                      } else if(tablero[i][j][1] == -1){
                          //j = j+1
                          //j = j+2 solo en la posición inicial 
                      }
                      continue;
                    case 2:
                       // afil
                       continue;
                     default:
                       // code block
                   }
               }
           }
       }


       return movimientos
   }
   // checar quien gana
   // obtener valor y terminar
   // obtener oponente
};

int main(){
    Chess juego; 
    juego.mostrarPiezas();
    juego.estado_inicial();
    return 0;
}