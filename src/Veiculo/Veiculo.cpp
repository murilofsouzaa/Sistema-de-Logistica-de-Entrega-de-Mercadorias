#include "include/Veiculo.hpp"
#include "../Local/include/Local.hpp"
#include <iostream>
#include <vector>

static std::vector<Veiculo> veiculos;

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