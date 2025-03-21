#include "chess.h"
#include <iostream>
#include <string>
//#include <time.h> // para la semilla aleatoria
using namespace std;

int jugador = -1,x,i=0,sum = 0;
Chess juego;
string player; 
string Gam_Englund[16] = {"D2-D4","E7-E5","D4-E5","D8-E7","G1-F3","B8-C6",
                          "C1-F4","E7-B4","F4-D2","B4-B2","D2-C3","F8-B4",
                          "D1-D2","B4-C3","D2-C3","B2-C1"};

void jugadas_aleatorias();

void juego_manual();

void seguir_partida();

int main(){
    //juego.mostrarPiezas();
    //cout << "blanco:-1 | negro:1"<< endl;
    juego.estado_inicial();
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
      if (juego.checar_jaque(jugador)){
        player  = jugador == -1 ? "Blanco" : "Negro";
        cout << "Jaque a rey "<< player << endl;
        juego.movimientos_validos_jaque(-1*jugador);
        juego.mostrar_movimientos(juego.moves_jaque);
        break;}
      jugador = juego.obtener_oponente(jugador);
      
    }
    cout<< "Media de movimientos válidos: "<< sum/i << endl; 
}


void juego_manual(){

  while(true){
    juego.visualizar_tablero();
    juego.movimientos = juego.movimientos_validos(jugador);
    juego.mostrar_movimientos(juego.movimientos);
    player  = jugador == -1 ? "Blanco" : "Negro";
    cout <<"Turno de jugador: " << player << endl;
    cout << "Elige tu movimiento: "; 
    cin >> x;
    juego.siguiente_estado(juego.movimientos[x]);
    cout << "Número de jugada: "<< i++ << endl;
   
    if (juego.checar_jaque(jugador)){
        player  = jugador == -1 ? "Blanco" : "Negro";
        cout << "Jaque a rey "<< player << endl;
        juego.movimientos_validos_jaque(-1*jugador);
        juego.mostrar_movimientos(juego.moves_jaque);
        break;}
      jugador = juego.obtener_oponente(jugador);
      
    }

  }

void seguir_partida(){
    for(int i= 0; i<= sizeof(Gam_Englund)/sizeof(Gam_Englund[0]); i++){
      juego.visualizar_tablero();
      juego.siguiente_estado(juego.notacion_a_movimiento(Gam_Englund[i]));
      cout << "Número de jugada: "<< i << endl;
      juego.obtener_oponente(jugador);
    }
    if (juego.checar_jaque(jugador)){
        player  = jugador == -1 ? "Blanco" : "Negro";
        cout << "Jaque a rey "<< player << endl;
        juego.movimientos_validos_jaque(-1*jugador);
        juego.mostrar_movimientos(juego.moves_jaque);
    }
}





