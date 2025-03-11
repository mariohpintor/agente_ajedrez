#include "Chess.h"
#include <iostream>
using namespace std;

int main(){
    Chess juego; 
    juego.mostrarPiezas();
    cout << "blanco:-1 | negro:1"<< endl;
    juego.estado_inicial();
    int jugador = -1,x,i=0,sum = 0;
    cout << "Jugadas aleatorias"<< endl;
    //cout <<"Elige jugador: ";
    //cin >> jugador;
    while(i<50){
      juego.visualizar_tablero(); // mejor en terminal con fondo blanco y texto negro
      juego.movimientos = juego.movimientos_validos(jugador);
      sum+= juego.movimientos.size();
      //cout << "Jugador: "<< jugador<< endl; 
      //juego.mostrar_movimientos(juego.movimientos);
      //cout <<"Número de movimientos válidos: "<< juego.movimientos.size()<< endl;
      cout << "Número de jugada: "<< i++ << endl;
      //cout << "Elige tu movimiento: "; 
      //cin >> x;
      x = rand()% juego.movimientos.size();
      //cout << x << endl;
      //sleep(1);
      juego.siguiente_estado(juego.movimientos[x]);
      //juego.movimientos.clear();
      if (juego.checar_jaque(jugador)){
        cout << "Jaque a rey "<< -1*jugador;
        juego.movimientos_validos_jaque(-1*jugador);
        juego.mostrar_movimientos(juego.moves_jaque);
        break;}
      //juego.movimientos.clear();
      jugador = juego.obtener_oponente(jugador);
      
    }
    cout<< "Media de movimientos validos: "<< sum/i ; 
    return 0;
}