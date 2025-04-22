#include <torch/torch.h>

const int NUM_ACCIONES = 467; // Máx. movimientos legales en ajedrez (ajustar según necesidad)

// Definición de la red
struct ChessNet : torch::nn::Module {
    ChessNet() {
        // Capas convolucionales para procesar el tablero (8x8x2)
        conv1 = register_module("conv1", torch::nn::Conv2d(torch::nn::Conv2dOptions(2, 32, 3).stride(1).padding(1)));
        conv2 = register_module("conv2", torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 64, 3).stride(1).padding(1)));
        
        // Capas fully connected para el valor (1) y políticas (NUM_ACCIONES)
        fc_valor = register_module("fc_valor", torch::nn::Linear(64 * 8 * 8, 1));
        fc_politica = register_module("fc_politica", torch::nn::Linear(64 * 8 * 8, NUM_ACCIONES));
    }

    // Forward pass
    std::pair<torch::Tensor, torch::Tensor> forward(torch::Tensor x) {
        x = torch::relu(conv1->forward(x)); // [batch, 32, 8, 8]
        x = torch::relu(conv2->forward(x));  // [batch, 64, 8, 8]
        x = x.view({-1, 64 * 8 * 8});       // Aplanar

        // Valor (1, 0, -1)
        torch::Tensor valor = torch::tanh(fc_valor->forward(x)); // Rango [-1, 1]

        // Políticas (probabilidades de acciones)
        torch::Tensor politicas = torch::softmax(fc_politica->forward(x), 1); // Softmax

        return {valor, politicas};
    }

    torch::nn::Conv2d conv1, conv2;
    torch::nn::Linear fc_valor, fc_politica;
};

// Convierte int[8][8][2] a tensor de LibTorch
torch::Tensor tablero_a_tensor(int tablero[8][8][2]) {
    torch::Tensor tensor = torch::zeros({1, 2, 8, 8}, torch::kInt32); // [batch, canales, filas, cols]

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            tensor[0][0][i][j] = tablero[i][j][0]; // Canal 1: piezas
            tensor[0][1][i][j] = tablero[i][j][1]; // Canal 2: colores
        }
    }

    return tensor.to(torch::kFloat32); // Convertir a float para la red
}

int main() {
    // Ejemplo de tablero: int[8][8][2]
    int tablero[8][8][2] = {
        {{4, 1}, {2, 1}, {3, 1}, {5, 1}, {6, 1}, {3, 1}, {2, 1}, {4, 1}},
        // ... (llenar con el estado real del tablero)
    };

    // Crear red y cargar pesos (si existen)
    ChessNet red;
    torch::load(red, "chess_net.pt"); // Opcional

    // Forward pass
    auto input = tablero_a_tensor(tablero);
    auto [valor, politicas] = red->forward(input);

    // Decodificar salidas
    float eval = valor.item<float>(); // Valor entre [-1, 1]
    std::cout << "Evaluación: " << eval << std::endl;

    // Mostrar top-3 acciones
    auto topk = torch::topk(politicas, 3);
    for (int i = 0; i < 3; ++i) {
        int accion = topk.indices[0][i].item<int>();
        float prob = topk.values[0][i].item<float>();
        std::cout << "Acción " << accion << ": " << prob * 100 << "%" << std::endl;
    }

    return 0;
}


// Ejemplo de bucle de entrenamiento
void entrenar(ChessNet& red, torch::optim::Optimizer& optimizador, 
              const std::vector<torch::Tensor>& datos, const std::vector<torch::Tensor>& etiquetas) {
    
    for (size_t i = 0; i < datos.size(); ++i) {
        optimizador.zero_grad();
        
        // Forward
        auto [valor_pred, politicas_pred] = red->forward(datos[i]);
        
        // Pérdidas (MSE para valor, CrossEntropy para políticas)
        torch::Tensor perdida_valor = torch::mse_loss(valor_pred, etiquetas[i].first);
        torch::Tensor perdida_politica = torch::cross_entropy_loss(politicas_pred, etiquetas[i].second);
        torch::Tensor perdida_total = perdida_valor + perdida_politica;
        
        // Backward
        perdida_total.backward();
        optimizador.step();
    }
}