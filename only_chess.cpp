#include "chess.h"
#include <iostream>
#include <string>
//#include <time.h> // para la semilla aleatoria
//#include<windows.h>
using namespace std;

int jugador = -1,x,i=0,sum = 0;
Chess juego;
string player; 
string Gam_Englund[16] = {"D2-D4","E7-E5","D4-E5","D8-E7","G1-F3","B8-C6",
                          "C1-F4","E7-B4","F4-D2","B4-B2","D2-C3","F8-B4",
                          "D1-D2","B4-C3","D2-C3","B2-C1"};
string Mate_pastor[7] = {"E2-E4","E7-E5","D1-H5","B8-C6","F1-C4","G8-F6","H5-F7"};
string Caro_Kann[11] = {"E2-E4","C7-C6","D2-D4","D7-D5","B1-C3","D5-E4",
                         "C3-E4","B8-D7","D1-E2","G8-F6","E4-D6"};
string partida_clavada[5] = {"D2-D4","C7-C5","E2-E4","D8-A5","C2-C3"};

void jugadas_aleatorias();

void juego_manual();

void seguir_partida();

int main(){
    //SetConsoleOutputCP(65001) //para visualizar en windows
    //juego.mostrarPiezas();
    //cout << "blanco:-1 | negro:1"<< endl;
    juego.estado_inicial();
    //std::cout << "\033[37m♟\033[0m" << std::endl;
    //std::cout << "\033[97m♟\033[0m" << std::endl;
    cout << "Selecciona una opción:"<< endl;
    cout << "1. Juego Normal"<<endl;
    cout << "2. Juego Aleatorio" <<endl;
    cout << "3. Seguir partida" <<endl;
    cout << "Opción: ";
    cin >> x;
    switch(x){
       case 1:
          juego_manual();
          break;
        case 2:
          jugadas_aleatorias();
          break;
        case 3:
          seguir_partida();
          break;
        default:
          cout << "Ingresa una opción válida."<< endl; 
    }

    return 0;
}

void jugadas_aleatorias(){
   // semillas que llegan a jaque: 3
   cout << "Semilla: ";
   cin >> x;
   srand (x); // semilla
   cout << "Jugadas aleatorias"<< endl;
      while(i<50){
      juego.visualizar_tablero(); 
      juego.movimientos = juego.movimientos_validos(jugador);
      sum+= juego.movimientos.size();
      cout << "Número de jugada: "<< i++ << endl;
      x = rand()% juego.movimientos.size();
      juego.siguiente_estado(juego.movimientos[x]);
      jugador = juego.obtener_oponente(jugador);
       if (juego.checar_jaque(jugador)){
        player  = jugador == -1 ? "Blanco" : "Negro";
        cout << "Jaque a rey "<< player << endl;
        juego.movimientos_validos_jaque(jugador);
        if (juego.checar_jaque_mate()){
            cout << "Jaque Mate"<< endl;
        } else{
           juego.mostrar_movimientos(juego.moves_jaque);}

       }
      
    }
    cout<< "Media de movimientos válidos: "<< sum/i << endl; 
}


void juego_manual(){

  while(true){
    juego.visualizar_tablero();
    juego.movimientos = juego.movimientos_validos(jugador);
    juego.clavadas(jugador,juego.movimientos); 
    //juego.checar_enroque(jugador,juego.movimientos);
    juego.mostrar_movimientos(juego.movimientos);
    //juego.mostrar_estado();
    player  = jugador == -1 ? "Blanco" : "Negro";
    cout <<"Turno de jugador: " << player << endl;
    cout << "Elige tu movimiento: "; 
    cin >> x;
    juego.siguiente_estado(juego.movimientos[x]);
    cout << "Número de jugada: "<< i++ << endl;
    juego.movimientos.clear();
    jugador = juego.obtener_oponente(jugador);
    
   if (juego.checar_jaque(jugador)){
        player  = jugador == -1 ? "Blanco" : "Negro";
        cout << "Jaque a rey "<< player << endl;
        juego.movimientos_validos_jaque(jugador);
        if (juego.checar_jaque_mate()){
            cout << "Jaque Mate"<< endl;
        } else{
           juego.mostrar_movimientos(juego.moves_jaque);}

    }

  }

}

void seguir_partida(){
    std::string* partidas[] = {Gam_Englund, Mate_pastor, Caro_Kann,partida_clavada};
    int tamanios[] = {16, 7, 11, 5};
    cout<< "Elige partida:"<<endl;
    cout<< "1. Gambito Englund"<<endl; // correct 
    cout << "2. Mate al pastor "<<endl; // correct
    cout << "3. Mate en la defensa Caro-Kann"<<endl; // jaque con clavada
    cout << "4. Ejemplo jaque simple"<<endl;
    cout<< "Opción: ";
    cin >> x;
    x--;
    jugador = -1;
    for(int i= 0; i< tamanios[x]; i++){
      juego.siguiente_estado(juego.notacion_a_movimiento(partidas[x][i]));
      juego.visualizar_tablero();
      cout << "Número de jugada: "<< i << "| Jugador: "<<jugador<< endl;
      jugador = juego.obtener_oponente(jugador);
      
      if (i==tamanios[x]-2){
         cout << "moves de "<< jugador << endl;
         juego.movimientos = juego.movimientos_validos(jugador);
         juego.mostrar_movimientos(juego.movimientos);
      }
    }
    //cout << jugador<<","<<juego.checar_jaque(jugador)<< endl;
    int rey[2];
      if(jugador == 1){
          rey[0] = juego.rey_negro[0];
          rey[1] = juego.rey_negro[1];}
      else{rey[0] = juego.rey_blanco[0];
          rey[1] = juego.rey_blanco[1];}
    cout << rey[0] <<"," << rey[1]<< endl;
    if (juego.checar_jaque(jugador)){
        player  = jugador == -1 ? "Blanco" : "Negro";
        cout << "Jaque a rey "<< player << endl;
        juego.movimientos_validos_jaque(jugador); // revisar
        cout << "#moves jaque: " <<juego.moves_jaque.size()<< endl;
        if (juego.checar_jaque_mate()){
            cout << "Jaque Mate"<< endl;
        } else{
           juego.mostrar_movimientos(juego.moves_jaque);}

    }
    cout << "moves de "<< -jugador << endl;
    juego.movimientos = juego.movimientos_validos(-jugador);
    juego.mostrar_movimientos(juego.movimientos);
    //juego.mostrar_movimientos(juego.movimientos2);

}





