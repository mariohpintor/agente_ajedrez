#include <iostream>
#include <vector>  // Incluir la biblioteca de vector

int main() {
    // Declarar un vector vacío de enteros
    std::vector<int> miVector;

    // Agregar elementos al vector
    miVector.push_back(10);  // Añade 10 al final
    miVector.push_back(20);  // Añade 20 al final
    miVector.push_back(30);  // Añade 30 al final

    // Acceder a los elementos
    std::cout << "Elementos del vector: ";
    for (int i = 0; i < miVector.size(); i++) {
        std::cout << miVector[i] << " ";
    }

    return 0;
}