#include "include/Pedido.hpp"
#include "../Veiculo/include/Veiculo.hpp"  
#include <iostream>
#include <vector>

// Definição da variável global pedidos (importante para linker)
std::vector<Pedido> pedidos;

Pedido::Pedido(int id, const std::string& origem, const std::string& destino, float peso)
    : id(id), nomeOrigem(origem), nomeDestino(destino), peso(peso), placaVeiculo(""), entregue(false) {}

Pedido::Pedido(int id, const std::string& origem, const std::string& destino, float peso, const std::string& placaVeiculo, bool entregue)
    : id(id), nomeOrigem(origem), nomeDestino(destino), peso(peso), placaVeiculo(placaVeiculo), entregue(entregue) {}

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
        std::cout << "ID: " << p.id
                  << " | Origem: " << p.nomeOrigem
                  << " | Destino: " << p.nomeDestino
                  << " | Peso: " << p.peso << "kg"
                  << " | Veículo: " << (p.placaVeiculo.empty() ? "Nenhum" : p.placaVeiculo)
                  << " | Status: " << (p.entregue ? "Entregue" : "Pendente") << "\n";
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

bool associarPedidoVeiculo(int idPedido, const std::string& placaVeiculo) {
    extern std::vector<Veiculo> veiculos;
    bool veiculoExiste = false;
    for (const Veiculo& v : veiculos) {
        if (v.placa == placaVeiculo) {
            veiculoExiste = true;
            break;
        }
    }
    if (!veiculoExiste) {
        std::cout << "Veículo não encontrado.\n";
        return false;
    }

    for (Pedido& p : pedidos) {
        if (p.id == idPedido) {
            if (!p.placaVeiculo.empty()) {
                std::cout << "Pedido já está associado a um veículo.\n";
                return false;
            }
            p.placaVeiculo = placaVeiculo;
            p.entregue = false;
            std::cout << "Pedido associado ao veículo com sucesso!\n";
            return true;
        }
    }
    std::cout << "Pedido não encontrado.\n";
    return false;
}

bool finalizarEntrega(int idPedido, const std::string& placaVeiculo) {
    extern std::vector<Veiculo> veiculos; 

    for (Pedido& p : pedidos) {
        if (p.id == idPedido) {
            if (p.placaVeiculo != placaVeiculo) {
                std::cout << "Pedido não está associado a esse veículo.\n";
                return false;
            }
            if (p.entregue) {
                std::cout << "Entrega já finalizada.\n";
                return false;
            }
            p.entregue = true;

            for (Veiculo& v : veiculos) {
                if (v.placa == placaVeiculo) {
                    v.status = "disponivel";
                    v.localAtual = p.nomeDestino;
                    break;
                }
            }
            std::cout << "Entrega finalizada com sucesso!\n";
            return true;
        }
    }
    std::cout << "Pedido não encontrado.\n";
    return false;
}
