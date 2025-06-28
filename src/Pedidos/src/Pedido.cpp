#include "Pedido.hpp"
#include <iostream>
#include <vector>

static std::vector<Pedido> pedidos;

Pedido::Pedido(int id, std::string origem, std::string destino, float peso)
    : id(id), nomeOrigem(origem), nomeDestino(destino), peso(peso) {}

bool cadastrarPedido(int id, const std::string& origem, const std::string& destino, float peso) {
    for (const Pedido& p : pedidos) {
        if (p.id == id) {
            std::cout << "Erro: já existe um pedido com esse ID.\n";
            return false;
        }
    }

    pedidos.emplace_back(id, origem, destino, peso);
    std::cout << "Pedido cadastrado com sucesso!\n";
    return true;
}

void listarPedidos() {
    if (pedidos.empty()) {
        std::cout << "Nenhum pedido cadastrado.\n";
        return;
    }

    std::cout << "Lista de pedidos:\n";
    for (const Pedido& p : pedidos) {
        std::cout << "ID: " << p.id << " | Origem: " << p.nomeOrigem
                  << " | Destino: " << p.nomeDestino << " | Peso: " << p.peso << "kg\n";
    }
}

bool atualizarPedido(int id, const std::string& novaOrigem, const std::string& novoDestino, float novoPeso) {
    for (Pedido& p : pedidos) {
        if (p.id == id) {
            p.nomeOrigem = novaOrigem;
            p.nomeDestino = novoDestino;
            p.peso = novoPeso;
            std::cout << "Pedido atualizado com sucesso!\n";
            return true;
        }
    }

    std::cout << "Pedido não encontrado.\n";
    return false;
}

bool excluirPedido(int id) {
    for (auto it = pedidos.begin(); it != pedidos.end(); ++it) {
        if (it->id == id) {
            pedidos.erase(it);
            std::cout << "Pedido excluído com sucesso!\n";
            return true;
        }
    }

    std::cout << "Pedido não encontrado.\n";
    return false;
}
