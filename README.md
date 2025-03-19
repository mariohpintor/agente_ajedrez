 # Agente de ajedrez (en construcción)

Un proyecto en c++ para entrenar varios agentes de ajedrez, para aplicar algunos métodos de Reinforcement Learning.

- Uno con Monte Carlo Tree Search usual
- Q-learning simple
- Uno basado en Alpha Zero

En ```chess.cpp``` está definida la clase del juego de ajedrez y  ```chess.h``` es  el encabezado para usar la clase como modulo, para compilarlo usa:
```bash 
 g++ -std=c++11 -o only_chess chess.cpp only_chess.cpp
```

En ```chess_mdp.cpp``` es lo mismo que lo anterior, pero en un solo archivo.

Esta parte es para crear el proceso de decisión de Markov que nos dara principalmente dado un estado las lista de acciones válidas. Y dada una acción el siguiente estado.

Para el MCTS, usamos la clase Nodo y MCTS, para compilarlo usamos ```dev.cpp```: 

```bash
g++ -std=c++11 -o dev_program nodo.cpp chess.cpp mcts.cpp dev.cpp
```