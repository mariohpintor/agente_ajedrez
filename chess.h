#ifndef CHESS_H  // Guardia de inclusión
#define CHESS_H

#include <string>
#include <vector>

// Definir colores ANSI
#define RESET   "\033[0m"
#define AZUL_OSCURO  "\033[48;5;21m"  
#define AZUL_CLARO "\033[48;5;69m"
#define TEXTO_NEGRO "\033[38;5;232m" 
#define TEXTO_BLANCO "\033[38;5;255m"

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
    //std::string figuras_blancas[6];
    std::string figuras_negras[6];
    std::string piezas[7];
    std::string columnas;
    int tablero[8][8][2];  // [fila][columna][color_pieza, tipo_pieza]
    int rey_blanco[2];
    int rey_negro[2];
    //int jaqueadora[2];
    std::vector<Coordenadas> movimientos, movimientos2;
    std::vector<Coordenadas> moves_jaque;
    std::vector<int> piezas_clavadas;
    int info_enroque;

    void mostrarPiezas();
    void estado_inicial();
    void estado_arbitrario(int estado_arb[][8][2]);
    void mostrar_estado();
    void siguiente_estado_copy(Coordenadas accion, int tablero[][8][2]);
    void siguiente_estado(Coordenadas accion);
    int minimo(int a, int b);
    void diagonales(int jugador,int i, int j,std::vector<Coordenadas>& movimientos);
    void rectas(int jugador,int i, int j,std::vector<Coordenadas>& movimientos);
    std::vector<Coordenadas>  movimientos_validos(int jugador);
    void checar_enroque(int jugador,std::vector<Coordenadas>& movimientos);
    void enroque(Coordenadas accion);
    std::string movimiento_a_notacion(Coordenadas accion);
    Coordenadas notacion_a_movimiento(std::string move);
    void mostrar_movimientos(std::vector<Coordenadas>& movimientos);
    void visualizar_tablero();
    void clavadas(int jugador,std::vector<Coordenadas>& movimientos);
    bool checar_jaque(int jugador);
    void movimientos_validos_jaque(int jugador);
    bool checar_jaque_mate();
    int valor_terminar(int jugador);
    int obtener_oponente(int jugador);
};

#endif