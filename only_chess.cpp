#include "chess.h"
#include <iostream>
//#include <time.h> // para la semilla aleatoria
using namespace std;

int jugador = -1,x,i=0,sum = 0;
Chess juego;
string player; 

void jugadas_aleatorias();

void juego_manual();

int main(){
    //juego.mostrarPiezas();
    //cout << "blanco:-1 | negro:1"<< endl;
    juego.estado_inicial();
    cout << "¿Quieres jugar o un juego aleatorio? 0|1: ";
    cin >> x;
    if (x==0){juego_manual();} else {jugadas_aleatorias();}
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
        //juego.mostrar_movimientos(juego.moves_jaque);
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
    jugador = juego.obtener_oponente(jugador);
    if (juego.checar_jaque(jugador)){
        player  = jugador == -1 ? "Blanco" : "Negro";
        cout << "Jaque a rey "<< player << endl;
        juego.movimientos_validos_jaque(jugador);
        juego.mostrar_movimientos(juego.moves_jaque);
        break;}
     
      
    }

  }





