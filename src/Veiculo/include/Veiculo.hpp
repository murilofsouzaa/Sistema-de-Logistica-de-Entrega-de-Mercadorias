#ifndef VEICULO_HPP
#define VEICULO_HPP

#include <string>
#include <vector>
#include <utility>

class Veiculo {
public:
    std::string placa;
    std::string modelo;
    std::string status;
    std::string localAtual;

    Veiculo(std::string placa, std::string modelo, std::string status, std::string localAtual);
};

bool cadastrarVeiculo(std::string placa, std::string modelo, std::string status, std::string localAtual);
void listarVeiculos();
bool atualizarVeiculo(std::string placa, std::string novoModelo, std::string novoStatus, std::string novoLocal);
bool excluirVeiculo(std::string placa);
void backupDados();
void restaurarDados();

std::string buscarVeiculoMaisProximo(float origemX, float origemY, const std::vector<std::string>& locais, const std::vector<std::pair<float, float>>& coordenadas);

#endif
