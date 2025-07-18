#include "Pedido.hpp"
#include "Veiculo.hpp"
#include "Local.hpp"
#include <iostream>
#include <vector>
#include <cmath>

std::vector<Pedido> pedidos;

Pedido::Pedido(int id, const std::string& origem, const std::string& destino, float peso)
    : id(id), nomeOrigem(origem), nomeDestino(destino), peso(peso), placaVeiculo(""), entregue(false) {}

Pedido::Pedido(int id, const std::string& origem, const std::string& destino, float peso,
               const std::string& placaVeiculo, bool entregue)
    : id(id), nomeOrigem(origem), nomeDestino(destino), peso(peso),
      placaVeiculo(placaVeiculo), entregue(entregue) {}

bool cadastrarPedido(int id, const std::string& origem, const std::string& destino, float peso) {
    for (const Pedido& p : pedidos) {
        if (p.id == id) {
            std::cout << "Erro: ja existe um pedido com esse ID.\n";
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
                  << " | Peso: " << p.peso << " kg"
                  << " | Veiculo: " << (p.placaVeiculo.empty() ? "Nenhum" : p.placaVeiculo)
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
    std::cout << "Pedido nao encontrado.\n";
    return false;
}

bool excluirPedido(int id) {
    for (auto it = pedidos.begin(); it != pedidos.end(); ++it) {
        if (it->id == id) {
            pedidos.erase(it);
            std::cout << "Pedido excluido com sucesso!\n";
            return true;
        }
    }
    std::cout << "Pedido nao encontrado.\n";
    return false;
}

bool associarPedidoVeiculo(int idPedido, const std::string& placaVeiculo) {
    extern std::vector<Veiculo> veiculos;
    Veiculo* veiculoPtr = nullptr;

    for (Veiculo& v : veiculos) {
        if (v.placa == placaVeiculo) {
            veiculoPtr = &v;
            break;
        }
    }
    if (!veiculoPtr) {
        std::cout << "Veiculo nao encontrado.\n";
        return false;
    }

    for (Pedido& p : pedidos) {
        if (p.id == idPedido) {
            if (!p.placaVeiculo.empty()) {
                std::cout << "Pedido ja esta associado a um veiculo.\n";
                return false;
            }
            p.placaVeiculo = placaVeiculo;
            p.entregue = false;
            veiculoPtr->status = "ocupado";
            std::cout << "Pedido associado ao veiculo com sucesso!\n";
            return true;
        }
    }
    std::cout << "Pedido nao encontrado.\n";
    return false;
}

bool finalizarEntrega(int idPedido, const std::string& placaVeiculo) {
    extern std::vector<Veiculo> veiculos;

    for (Pedido& p : pedidos) {
        if (p.id == idPedido) {
            if (p.placaVeiculo != placaVeiculo) {
                std::cout << "Pedido nao esta associado a esse veiculo.\n";
                return false;
            }
            if (p.entregue) {
                std::cout << "Entrega ja finalizada.\n";
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
    std::cout << "Pedido nao encontrado.\n";
    return false;
}

void mostrarDistanciaPedido(int id) {
    Pedido* pedidoEncontrado = nullptr;
    for (Pedido& p : pedidos) {
        if (p.id == id) {
            pedidoEncontrado = &p;
            break;
        }
    }
    if (!pedidoEncontrado) {
        std::cout << "Pedido nao encontrado.\n";
        return;
    }

    Local* origem = buscarLocalPorNome(pedidoEncontrado->nomeOrigem);
    Local* destino = buscarLocalPorNome(pedidoEncontrado->nomeDestino);

    if (!origem || !destino) {
        std::cout << "Origem ou destino nao encontrados.\n";
        return;
    }

    float distancia = calcularDistanciaEntreLocais(*origem, *destino);
    std::cout << "Distancia entre origem e destino do pedido " << id << ": " << distancia << " unidades.\n";
}
