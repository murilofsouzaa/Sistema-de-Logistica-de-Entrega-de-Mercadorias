#include <iostream>
#include "Veiculo.hpp"

int main() {
    std::cout << "Cadastrando veiculo...\n";
    cadastrarVeiculo("ABC1234", "Fiorino", "disponivel", "Centro");
    cadastrarVeiculo("XYZ5678", "Kombi", "disponivel", "Bairro A");
    listarVeiculos();

    std::cout << "\nTentando cadastrar veiculo com placa repetida...\n";
    cadastrarVeiculo("ABC1234", "Uno", "disponivel", "Centro");

    std::cout << "\nAtualizando veiculo...\n";
    atualizarVeiculo("XYZ5678", "Kombi Nova", "ocupado", "Bairro B");
    listarVeiculos();

    std::cout << "\nExcluindo veiculo...\n";
    excluirVeiculo("XYZ5678");
    listarVeiculos();

    std::cout << "\nTentando excluir veiculo inexistente...\n";
    excluirVeiculo("ZZZ0000");

    std::cout << "\nTestes manuais de Veiculo finalizados!\n";
    return 0;
}