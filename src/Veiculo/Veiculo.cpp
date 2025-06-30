#include "include/Veiculo.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

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

void backupDados() {
    std::ofstream outFile("veiculos_backup.dat", std::ios::binary);
    if (!outFile) return;

    size_t tamanho = veiculos.size();
    outFile.write(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    for (const Veiculo& v : veiculos) {
        size_t tamPlaca = v.placa.size();
        size_t tamModelo = v.modelo.size();
        size_t tamStatus = v.status.size();
        size_t tamLocal = v.localAtual.size();

        outFile.write(reinterpret_cast<char*>(&tamPlaca), sizeof(tamPlaca));
        outFile.write(v.placa.c_str(), tamPlaca);

        outFile.write(reinterpret_cast<char*>(&tamModelo), sizeof(tamModelo));
        outFile.write(v.modelo.c_str(), tamModelo);

        outFile.write(reinterpret_cast<char*>(&tamStatus), sizeof(tamStatus));
        outFile.write(v.status.c_str(), tamStatus);

        outFile.write(reinterpret_cast<char*>(&tamLocal), sizeof(tamLocal));
        outFile.write(v.localAtual.c_str(), tamLocal);
    }

    outFile.close();
    std::cout << "Backup realizado com sucesso!\n";
}

void restaurarDados() {
    std::ifstream inFile("veiculos_backup.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "Arquivo de backup não encontrado.\n";
        return;
    }

    veiculos.clear();
    size_t tamanho;
    inFile.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    for (size_t i = 0; i < tamanho; ++i) {
        size_t tamPlaca, tamModelo, tamStatus, tamLocal;
        inFile.read(reinterpret_cast<char*>(&tamPlaca), sizeof(tamPlaca));
        std::string placa(tamPlaca, ' ');
        inFile.read(&placa[0], tamPlaca);

        inFile.read(reinterpret_cast<char*>(&tamModelo), sizeof(tamModelo));
        std::string modelo(tamModelo, ' ');
        inFile.read(&modelo[0], tamModelo);

        inFile.read(reinterpret_cast<char*>(&tamStatus), sizeof(tamStatus));
        std::string status(tamStatus, ' ');
        inFile.read(&status[0], tamStatus);

        inFile.read(reinterpret_cast<char*>(&tamLocal), sizeof(tamLocal));
        std::string localAtual(tamLocal, ' ');
        inFile.read(&localAtual[0], tamLocal);

        veiculos.emplace_back(placa, modelo, status, localAtual);
    }

    inFile.close();
    std::cout << "Dados restaurados com sucesso!\n";
}

std::string buscarVeiculoMaisProximo(float origemX, float origemY, const std::vector<std::string>& locais, const std::vector<std::pair<float, float>>& coordenadas) {
    float menorDistancia = 1e9;
    std::string placaMaisProxima = "";

    for (const Veiculo& v : veiculos) {
        if (v.status != "disponível") continue;

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
