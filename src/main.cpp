#include <iostream>
#include <string>
#include <vector>
#include "./Local/include/Local.hpp"
#include "./Pedido/include/Pedido.hpp"
#include "./Veiculo/include/Veiculo.hpp"
#include "./Rota/include/Rota.hpp"

using namespace std;

int proximoIdPedido = 1;

int main() {
    // 1. Cadastro de locais
    cadastrarLocal("Centro", 0, 0);
    cadastrarLocal("Bairro A", 10, 0);
    cadastrarLocal("Bairro B", 0, 10);
    cadastrarLocal("Bairro C", 10, 10);

    cout << "\n--- Locais cadastrados ---\n";
    listarLocais();

    // 2. Cadastro de veículos
    cout << "\n--- Cadastro de veículos ---\n";
    cadastrarVeiculo("ABC1234", "Fiorino", "disponivel", "Centro");
    cadastrarVeiculo("XYZ5678", "Kombi", "disponivel", "Bairro A");
    listarVeiculos();

    // Atualizar veículo
    atualizarVeiculo("XYZ5678", "Kombi 2024", "disponivel", "Bairro C");
    listarVeiculos();

    // Excluir veículo
    excluirVeiculo("XYZ5678");
    listarVeiculos();

    // 3. Cadastro de pedidos
    cout << "\n--- Cadastro de pedidos ---\n";
    cadastrarPedido(proximoIdPedido++, "Centro", "Bairro B", 5.0);
    cadastrarPedido(proximoIdPedido++, "Bairro A", "Bairro C", 3.0);
    listarPedidos();

    // Atualizar pedido
    atualizarPedido(1, "Centro", "Bairro C", 6.0);
    listarPedidos();

    // Excluir pedido
    excluirPedido(2);
    listarPedidos();

    // 4. Associação pedido -> veículo
    cout << "\n--- Associação de pedido ao veículo ---\n";
    associarPedidoVeiculo(1, "ABC1234");
    listarVeiculos();

    // 5. Cálculo de distância entre locais pelo nome
    cout << "\n--- Cálculo de distância ---\n";
    float distancia = calcularDistanciaEntreLocaisPorNome("Centro", "Bairro C");
    if (distancia >= 0)
        cout << "Distância entre Centro e Bairro C: " << distancia << " km\n";
    else
        cout << "Erro ao calcular distância: um dos locais não foi encontrado.\n";

    // 6. Teste do cálculo de rota de entrega
    cout << "\n--- Cálculo de rota de entrega ---\n";
    vector<string> locaisParaRota = {"Centro", "Bairro A", "Bairro B", "Bairro C"};
    vector<string> rota = calcularRotaEntrega(locaisParaRota);

    cout << "Rota calculada:\n";
    for (const auto& local : rota) {
        cout << local << " -> ";
    }
    cout << "Fim\n";

    // 7. Finalizar entrega
    finalizarEntrega(1, "ABC1234");
    listarVeiculos();

    return 0;
}
