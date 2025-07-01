#include "../Veiculo/include/Veiculo.hpp"
#include "../Local/include/Local.hpp"
#include "../Pedido/include/Pedido.hpp"
#include "include/recuperarDados.hpp"

#include <fstream>
#include <iostream>

extern std::vector<Veiculo> veiculos;

extern Local locais[];
extern int qtdLocais;

extern std::vector<Pedido> pedidos;

void lerString(std::ifstream& in, std::string& str) {
    size_t tamanho;
    in.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    str.resize(tamanho);
    in.read(&str[0], tamanho);
}

void restaurarVeiculos() {
    std::ifstream inFile("veiculos_backup.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "Arquivo de backup de veiculos nao encontrado.\n";
        return;
    }

    veiculos.clear();
    size_t tamanho;
    inFile.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    for (size_t i = 0; i < tamanho; i++) {
        std::string placa, modelo, status, localAtual;
        lerString(inFile, placa);
        lerString(inFile, modelo);
        lerString(inFile, status);
        lerString(inFile, localAtual);
        veiculos.emplace_back(placa, modelo, status, localAtual);
    }
    inFile.close();
    std::cout << "Restauracao de veiculos concluida com sucesso!\n";
}

void restaurarLocais() {
    std::ifstream inFile("locais_backup.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "Arquivo de backup de locais nao encontrado.\n";
        return;
    }

    inFile.read(reinterpret_cast<char*>(&qtdLocais), sizeof(qtdLocais));
    for (int i = 0; i < qtdLocais; i++) {
        std::string nome;
        float x, y;
        lerString(inFile, nome);
        inFile.read(reinterpret_cast<char*>(&x), sizeof(x));
        inFile.read(reinterpret_cast<char*>(&y), sizeof(y));
        locais[i] = Local(nome, x, y);
    }
    inFile.close();
    std::cout << "Restauracao de locais concluida com sucesso!\n";
}

void restaurarPedidos() {
    std::ifstream inFile("pedidos_backup.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "Arquivo de backup de pedidos nao encontrado.\n";
        return;
    }

    pedidos.clear();
    size_t tamanho;
    inFile.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    for (size_t i = 0; i < tamanho; i++) {
        int id;
        std::string nomeOrigem, nomeDestino, placaVeiculo;
        float peso;
        bool entregue;

        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        lerString(inFile, nomeOrigem);
        lerString(inFile, nomeDestino);
        inFile.read(reinterpret_cast<char*>(&peso), sizeof(peso));
        lerString(inFile, placaVeiculo);
        inFile.read(reinterpret_cast<char*>(&entregue), sizeof(entregue));

        pedidos.emplace_back(id, nomeOrigem, nomeDestino, peso, placaVeiculo, entregue);
    }
    inFile.close();
    std::cout << "Restauracao de pedidos concluida com sucesso!\n";
}

void restaurarDados() {
    restaurarVeiculos();
    restaurarLocais();
    restaurarPedidos();
}
