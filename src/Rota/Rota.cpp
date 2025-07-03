#include "Rota.hpp"
#include "Local.hpp"
#include <iostream>
#include <limits>
#include <cmath>

float distanciaEntreLocais(const std::string& nome1, const std::string& nome2) {
    return calcularDistanciaEntreLocaisPorNome(nome1, nome2);
}

std::vector<std::string> calcularRotaEntrega(const std::vector<std::string>& nomesLocais) {
    if (nomesLocais.empty()) return {};

    std::vector<std::string> rota;
    std::vector<bool> visitado(nomesLocais.size(), false);

    int atual = 0;
    rota.push_back(nomesLocais[atual]);
    visitado[atual] = true;

    for (size_t i = 1; i < nomesLocais.size(); ++i) {
        float menorDistancia = std::numeric_limits<float>::max();
        int proximo = -1;

        for (size_t j = 0; j < nomesLocais.size(); ++j) {
            if (!visitado[j]) {
                float dist = distanciaEntreLocais(nomesLocais[atual], nomesLocais[j]);
                if (dist < menorDistancia) {
                    menorDistancia = dist;
                    proximo = (int)j;
                }
            }
        }

        if (proximo == -1) break;

        rota.push_back(nomesLocais[proximo]);
        visitado[proximo] = true;
        atual = proximo;
    }

    return rota;
}
