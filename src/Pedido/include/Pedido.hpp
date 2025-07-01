#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <string>

class Pedido {
public:
    int id;
    std::string nomeOrigem;
    std::string nomeDestino;
    float peso;

    std::string placaVeiculo; // veículo associado
    bool entregue;            // status da entrega

    // Construtor básico
    Pedido(int id, const std::string& origem, const std::string& destino, float peso);

    // Construtor completo para recuperação dos dados
    Pedido(int id, const std::string& origem, const std::string& destino, float peso, const std::string& placaVeiculo, bool entregue);
};

// CRUD
bool cadastrarPedido(int id, const std::string& origem, const std::string& destino, float peso);
void listarPedidos();
bool atualizarPedido(int id, const std::string& novaOrigem, const std::string& novoDestino, float novoPeso);
bool excluirPedido(int id);

bool associarPedidoVeiculo(int idPedido, const std::string& placaVeiculo);
bool finalizarEntrega(int idPedido, const std::string& placaVeiculo);

#endif // PEDIDO_HPP
