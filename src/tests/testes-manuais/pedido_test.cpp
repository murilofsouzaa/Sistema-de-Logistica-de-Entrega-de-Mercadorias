#include <iostream>
#include "../../Pedido/include/Pedido.hpp"
#include "../../Veiculo/include/Veiculo.hpp"
#include "../../Local/include/Local.hpp"

int main() {
    cadastrarLocal("Origem", 0.0f, 0.0f);
    cadastrarLocal("Destino", 10.0f, 0.0f);

    Pedido p1(1, "Origem", "Destino", 5.0f);
    std::cout << "Esperado: id=1, Origem=Origem, Destino=Destino, Peso=5\n";
    std::cout << "Obtido: id=" << p1.id << ", Origem=" << p1.nomeOrigem << ", Destino=" << p1.nomeDestino << ", Peso=" << p1.peso << "\n\n";

    std::cout << "Cadastrando pedido...\n";
    cadastrarPedido(2, "Origem", "Destino", 8.0f);
    listarPedidos();

    std::cout << "\nAtualizando pedido...\n";
    atualizarPedido(2, "Origem", "Destino", 10.0f);
    listarPedidos();

    std::cout << "\nCadastrando veiculo e associando ao pedido...\n";
    cadastrarVeiculo("ABC1234", "Fiorino", "disponivel", "Origem");
    associarPedidoVeiculo(2, "ABC1234");
    listarPedidos();

    std::cout << "\nFinalizando entrega...\n";
    finalizarEntrega(2, "ABC1234");
    listarPedidos();

    std::cout << "\nDistancia do pedido:\n";
    mostrarDistanciaPedido(2);

    std::cout << "\nExcluindo pedido...\n";
    excluirPedido(2);
    listarPedidos();

    std::cout << "\nTestes manuais de Pedido finalizados!\n";
    return 0;
}