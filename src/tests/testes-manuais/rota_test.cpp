#include <iostream>
#include <vector>
#include "Rota.hpp"
#include "Local.hpp"

float distanciaEntreLocais(const std::string& nome1, const std::string& nome2);

int main() {
    cadastrarLocal("A", 0.0f, 0.0f);
    cadastrarLocal("B", 3.0f, 0.0f);
    cadastrarLocal("C", 3.0f, 4.0f);
    cadastrarLocal("D", 0.0f, 4.0f);

    std::vector<std::string> nomesLocais = {"A", "B", "C", "D"};

    std::cout << "Esperado: rota otima (A, B, C, D ou similar)\n";
    std::vector<std::string> rota = calcularRotaEntrega(nomesLocais);

    std::cout << "Obtido: ";
    for (const auto& nome : rota) {
        std::cout << nome << " ";
    }
    std::cout << "\n";

    float distAB = distanciaEntreLocais("A", "B");
    float distBC = distanciaEntreLocais("B", "C");
    std::cout << "Distancia de A para B: " << distAB << "\n";
    std::cout << "Distancia de B para C: " << distBC << "\n";

    std::cout << "Teste manual de rota finalizado!\n";
    return 0;
}