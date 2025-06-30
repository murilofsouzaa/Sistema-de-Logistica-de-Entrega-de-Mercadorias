#ifndef VEICULO_HPP
#define VEICULO_HPP

#include <string>
#include <vector>  // para o extern
#include <cmath> 

class Veiculo {
public:
    std::string placa;
    std::string modelo;
    std::string status;
    std::string localAtual;

    Veiculo(std::string placa, std::string modelo, std::string status, std::string localAtual);
};

// CRUD de Veículos
bool cadastrarVeiculo(std::string placa, std::string modelo, std::string status, std::string localAtual);
void listarVeiculos();
bool atualizarVeiculo(std::string placa, std::string novoModelo, std::string novoStatus, std::string novoLocal);
bool excluirVeiculo(std::string placa);

extern std::vector<Veiculo> veiculos;

#endif
