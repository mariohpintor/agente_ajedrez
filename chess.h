#ifndef CHESS_H  // Guardia de inclusión
#define CHESS_H

#include <string>
#include <vector>

// Definir la estructura Coordenadas
struct Coordenadas {
    int x;
    int y;
    int z;
    int w;
};

// Declarar la clase Chess
class Chess {
public:
    // Constructor
    Chess();

    // Variables miembro
    std::string figuras_blancas[6];
    std::string figuras_negras[6];
    std::string piezas[7];
    int tablero[8][8][3];  // [fila][columna][color_casilla, color_pieza, tipo_pieza]
    int rey_blanco[2];
    int rey_negro[2];
    std::vector<Coordenadas> movimientos;
    std::vector<Coordenadas> moves_jaque;
    Coordenadas info_enroque;

    void mostrarPiezas();
    void estado_inicial();
    void mostrar_estado();
    void siguiente_estado(Coordenadas accion);
    int minimo(int a, int b);
    std::vector<Coordenadas>  movimientos_validos(int jugador);
    void checar_enroque(int jugador);
    void enroque(int tipo_enroque);
    void mostrar_movimientos(std::vector<Coordenadas> movimientos);
    void visualizar_tablero();
    bool checar_jaque(int jugador);
    void movimientos_validos_jaque(int jugador);
    bool checar_jaque_mate(int jugador);
    int valor_terminar(int jugador);
    int obtener_oponente(int jugador);
};

#endif