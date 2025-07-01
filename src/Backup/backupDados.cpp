#include ".../../../include/Veiculo.hpp"
#include "../../../include/Local.hpp"
#include "../../../include/Pedido.hpp"
#include "include/backupDados.hpp"

#include <fstream>
#include <iostream>

extern std::vector<Veiculo> veiculos;

extern Local locais[];
extern int qtdLocais;

extern std::vector<Pedido> pedidos;

void escreverString(std::ofstream& out, const std::string& str) {
    size_t tamanho = str.size();
    out.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    out.write(str.c_str(), tamanho);
}

void backupVeiculos() {
    std::ofstream outFile("veiculos_backup.dat", std::ios::binary);
    if (!outFile) {
        std::cout << "Erro ao abrir arquivo de backup de veiculos.\n";
        return;
    }

    size_t tamanho = veiculos.size();
    outFile.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));

    for (const Veiculo& v : veiculos) {
        escreverString(outFile, v.placa);
        escreverString(outFile, v.modelo);
        escreverString(outFile, v.status);
        escreverString(outFile, v.localAtual);
    }

    outFile.close();
    std::cout << "Backup de veiculos realizado com sucesso!\n";
}

void backupLocais() {
    std::ofstream outFile("locais_backup.dat", std::ios::binary);
    if (!outFile) {
        std::cout << "Erro ao abrir arquivo de backup de locais.\n";
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&qtdLocais), sizeof(qtdLocais));

    for (int i = 0; i < qtdLocais; i++) {
        escreverString(outFile, locais[i].getNome());
        float x = locais[i].getX();
        float y = locais[i].getY();
        outFile.write(reinterpret_cast<const char*>(&x), sizeof(x));
        outFile.write(reinterpret_cast<const char*>(&y), sizeof(y));
    }

    outFile.close();
    std::cout << "Backup de locais realizado com sucesso!\n";
}

void backupPedidos() {
    std::ofstream outFile("pedidos_backup.dat", std::ios::binary);
    if (!outFile) {
        std::cout << "Erro ao abrir arquivo de backup de pedidos.\n";
        return;
    }

    size_t tamanho = pedidos.size();
    outFile.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));

    for (const Pedido& p : pedidos) {
        outFile.write(reinterpret_cast<const char*>(&p.id), sizeof(p.id));
        escreverString(outFile, p.nomeOrigem);
        escreverString(outFile, p.nomeDestino);
        outFile.write(reinterpret_cast<const char*>(&p.peso), sizeof(p.peso));
        escreverString(outFile, p.placaVeiculo);
        outFile.write(reinterpret_cast<const char*>(&p.entregue), sizeof(p.entregue));
    }

    outFile.close();
    std::cout << "Backup de pedidos realizado com sucesso!\n";
}

void backupDados() {
    backupVeiculos();
    backupLocais();
    backupPedidos();
}

