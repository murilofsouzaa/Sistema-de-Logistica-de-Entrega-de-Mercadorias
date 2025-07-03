#include <iostream>
#include <locale>
#include "Menu.hpp"
#include "Veiculo.hpp"
#include "Local.hpp"
#include "Pedido.hpp"
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

Veiculo* veiculoMaisProximo(const std::string& origem) {
    extern std::vector<Veiculo> veiculos;
    extern Local locais[];
    extern int qtdLocais;

    Local* localOrigem = buscarLocalPorNome(origem);
    if (!localOrigem) return nullptr;

    Veiculo* veiculoProx = nullptr;
    float minDist = std::numeric_limits<float>::max();

    for (Veiculo& v : veiculos) {
        if (v.status == "disponivel") {
            Local* localV = buscarLocalPorNome(v.localAtual);
            if (localV) {
                float dist = calcularDistanciaEntreLocais(*localOrigem, *localV);
                if (dist < minDist) {
                    minDist = dist;
                    veiculoProx = &v;
                }
            }
        }
    }
    return veiculoProx;
}

void calcularEExibirRotaEntrega() {
    extern std::vector<Pedido> pedidos;
    if (pedidos.empty()) {
        cout << "Nenhum pedido cadastrado.\n";
        return;
    }

    cout << "Pedidos pendentes:\n";
    for (const Pedido& p : pedidos) {
        if (!p.entregue) {
            cout << "ID: " << p.id << " | Origem: " << p.nomeOrigem << " | Destino: " << p.nomeDestino << " | Peso: " << p.peso << "kg\n";
        }
    }

    int idPedido;
    cout << "Digite o ID do pedido para calcular a rota: ";
    cin >> idPedido;

    Pedido* pedido = nullptr;
    for (Pedido& p : pedidos) {
        if (p.id == idPedido && !p.entregue) {
            pedido = &p;
            break;
        }
    }
    if (!pedido) {
        cout << "Pedido nao encontrado ou ja entregue.\n";
        return;
    }

    Veiculo* veiculo = veiculoMaisProximo(pedido->nomeOrigem);
    if (!veiculo) {
        cout << "Nenhum veiculo disponivel para entrega.\n";
        return;
    }

    Local* localOrigem = buscarLocalPorNome(pedido->nomeOrigem);
    Local* localDestino = buscarLocalPorNome(pedido->nomeDestino);
    Local* localVeiculo = buscarLocalPorNome(veiculo->localAtual);

    if (!localOrigem || !localDestino || !localVeiculo) {
        cout << "Erro ao localizar origem, destino ou veiculo.\n";
        return;
    }

    float distAteOrigem = calcularDistanciaEntreLocais(*localVeiculo, *localOrigem);
    float distEntrega = calcularDistanciaEntreLocais(*localOrigem, *localDestino);
    float distTotal = distAteOrigem + distEntrega;

    cout << "\n--- Rota de Entrega ---\n";
    cout << "Veiculo selecionado: " << veiculo->placa << " (" << veiculo->modelo << ")\n";
    cout << "Local atual do veiculo: " << veiculo->localAtual << "\n";
    cout << "Origem do pedido: " << pedido->nomeOrigem << "\n";
    cout << "Destino do pedido: " << pedido->nomeDestino << "\n";
    cout << "Distancia ate origem: " << distAteOrigem << "\n";
    cout << "Distancia da entrega: " << distEntrega << "\n";
    cout << "Distancia total percorrida: " << distTotal << "\n";

    cout << "\nSimular entrega? (S/N): ";
    char resp;
    cin >> resp;
    if (resp == 'S' || resp == 's') {
        veiculo->status = "ocupado";
        cout << "Veiculo agora esta 'ocupado'. Entregando...\n";

        veiculo->status = "disponivel";
        veiculo->localAtual = pedido->nomeDestino;
        pedido->entregue = true;
        pedido->placaVeiculo = veiculo->placa;
        cout << "Entrega concluida!\n";
        cout << "Veiculo agora esta 'disponivel' em " << veiculo->localAtual << ".\n";
    }
}

void inserirDadosTeste() {
    cadastrarLocal("Centro", 0.0f, 0.0f);
    cadastrarLocal("Bairro A", 10.0f, 0.0f);
    cadastrarLocal("Bairro B", 0.0f, 10.0f);

    cadastrarVeiculo("ABC1234", "Fiorino", "disponivel", "Centro");
    cadastrarVeiculo("XYZ5678", "Kombi", "disponivel", "Bairro A");

    cadastrarPedido(1, "Centro", "Bairro A", 5.0f);
    cadastrarPedido(2, "Bairro A", "Bairro B", 8.0f);
    cadastrarPedido(3, "Centro", "Bairro B", 2.5f);
}

int main() {
    std::setlocale(LC_ALL, "");

    int opcao;

    inserirDadosTeste();

    do {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1 - Gerenciar Locais\n";
        cout << "2 - Gerenciar Veiculos\n";
        cout << "3 - Gerenciar Pedidos\n";
        cout << "4 - Calcular e Exibir Rota de Entrega\n";
        cout << "5 - Fazer Backup dos Dados\n";
        cout << "6 - Restaurar Dados do Backup\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                menuLocais();
                break;
            case 2:
                menuVeiculos();
                break;
            case 3:
                menuPedidos();
                break;
            case 4:
                calcularEExibirRotaEntrega();
                break;
            case 5:
                backupDados();
                break;
            case 6:
                restaurarDados();
                break;
            case 0:
                cout << "Encerrando o sistema.\n";
                break;
            default:
                cout << "Opcao invalida.\n";
        }
    } while (opcao != 0);

    return 0;
}

//Para compilar: "g++ src/main.cpp src/Local/Local.cpp src/Veiculo/Veiculo.cpp src/Pedido/Pedido.cpp src/Rota/Rota.cpp src/Menu/Menu.cpp src/Backup/backupDados.cpp src/Backup/recuperarDados.cpp -Iinclude -o src/output/main.exe"

// Para executar: "src/output/main.exe"