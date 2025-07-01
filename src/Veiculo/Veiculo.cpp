#include "include/Veiculo.hpp"
#include <iostream>
#include <vector>
#include <cmath>

std::vector<Veiculo> veiculos;

Veiculo::Veiculo(std::string placa, std::string modelo, std::string status, std::string localAtual)
    : placa(placa), modelo(modelo), status(status), localAtual(localAtual) {}

bool cadastrarVeiculo(std::string placa, std::string modelo, std::string status, std::string localAtual) {
    for (const Veiculo& v : veiculos) {
        if (v.placa == placa) {
            std::cout << "Erro: já existe um veículo com essa placa.\n";
            return false;
        }
    }
    veiculos.emplace_back(placa, modelo, status, localAtual);
    std::cout << "Veículo cadastrado com sucesso!\n";
    return true;
}

void listarVeiculos() {
    if (veiculos.empty()) {
        std::cout << "Nenhum veículo cadastrado.\n";
        return;
    }

    std::cout << "Lista de veículos:\n";
    for (const Veiculo& v : veiculos) {
        std::cout << "Placa: " << v.placa << " | Modelo: " << v.modelo
                  << " | Status: " << v.status << " | Local Atual: " << v.localAtual << "\n";
    }
}

bool atualizarVeiculo(std::string placa, std::string novoModelo, std::string novoStatus, std::string novoLocal) {
    for (Veiculo& v : veiculos) {
        if (v.placa == placa) {
            v.modelo = novoModelo;
            v.status = novoStatus;
            v.localAtual = novoLocal;
            std::cout << "Veículo atualizado com sucesso!\n";
            return true;
        }
    }

    std::cout << "Veículo não encontrado.\n";
    return false;
}

bool excluirVeiculo(std::string placa) {
    for (auto it = veiculos.begin(); it != veiculos.end(); ++it) {
        if (it->placa == placa) {
            veiculos.erase(it);
            std::cout << "Veículo excluído com sucesso!\n";
            return true;
        }
    }

    std::cout << "Veículo não encontrado.\n";
    return false;
}

std::string buscarVeiculoMaisProximo(float origemX, float origemY, const std::vector<std::string>& locais, const std::vector<std::pair<float, float>>& coordenadas) {
    float menorDistancia = 1e9;
    std::string placaMaisProxima = "";

    for (const Veiculo& v : veiculos) {
        if (v.status != "disponivel") continue;

        for (size_t i = 0; i < locais.size(); ++i) {
            if (locais[i] == v.localAtual) {
                float dx = origemX - coordenadas[i].first;
                float dy = origemY - coordenadas[i].second;
                float distancia = std::sqrt(dx * dx + dy * dy);

                if (distancia < menorDistancia) {
                    menorDistancia = distancia;
                    placaMaisProxima = v.placa;
                }
                break;
            }
        }
    }

    return placaMaisProxima;
}
