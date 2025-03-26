 # Agente de ajedrez (en construcción)

Un proyecto en c++ para entrenar varios agentes de ajedrez, para aplicar algunos métodos de Reinforcement Learning.

- Uno con Monte Carlo Tree Search usual
- Q-learning simple
- Uno basado en Alpha Zero

En ```chess.cpp``` está definida la clase del juego de ajedrez y  ```chess.h``` es  el encabezado para usar la clase como modulo, para compilarlo usa:
```bash 
 g++ -std=c++11 -o only_chess chess.cpp only_chess.cpp
```

En ```chess_mdp.cpp``` es lo mismo que lo anterior de una versión no actualizada, pero en un solo archivo.

Esta parte es para crear el proceso de decisión de Markov que nos dara principalmente dado un estado las lista de acciones válidas. Y dada una acción el siguiente estado.

Para el MCTS, usamos la clase Nodo y MCTS, para compilarlo usamos ```dev.cpp```: 

```bash
g++ -std=c++11 -o dev_program nodo.cpp chess.cpp mcts.cpp dev.cpp
```

Para usar las funciones de vizualización asegúrate de que tu terminal soporte caracteres Unicode y colores ANSI.

## Notación para movimientos
Existen varias convenciones para anotar movimientos como la **algebraica**, aquí se usa notación **Coordenadas**. Por ejemplo:

|**Algebraica**| **Coordenadas**|
| :------------:| :----------------: |
|e4  e5       |  E2-E4 E7-E5|
|Cf3 Cc6  | G1-F3 B8-C6|
| Axc6 dxc6 |  B5-C6 D7-C6|
 |d3 Ab4+ | D2-D3 F8-B4|
| 0-0 Axc3 | E1-G1 B4-C3|

Otros simbolos importantes:
- 0-0 significa enroque corto
- 0-0-0 significa enroque largo
- "+" significa jaque
- "#", "++", "≠" o "‡" significa jaque mate

Y cada pieza usualmente se refiere a ella con la inicial del nombre de la pieza, excepto los peones.

## Ejemplos para verificar funcionamiento de reglas
**Mate al pastor**:  
1. E4 E5 
2. D1-H5 B8-C6 
3. F1-C4 G8-F6 
4. H5-F7#


**Mate en la defensa Caro-Kann**:
1. E2-E4 C7-C6
2. D2-D4 D7-D5
3. B1-C3 D5-E4
4. C3-E4 B8-D7
5. D1-E2 G8-F6
6. E4-D6#


## Cosas por corregir
- Peon A2 bug
- Posible error cuando hay dos amenazas a pieza clavada
- Si se mueven REY y TORRES y regresan a la posición de enroque no es distinguible
- Simular partidas completas para ver si hay errores
