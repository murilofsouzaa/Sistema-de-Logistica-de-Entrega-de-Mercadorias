#ifndef VEICULO_HPP
#define VEICULO_HPP

#include <string>

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

#endif