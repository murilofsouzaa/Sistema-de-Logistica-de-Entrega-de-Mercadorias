#include "Menu.hpp"
#include "Local.hpp"
#include "Veiculo.hpp"
#include "Pedido.hpp"
#include <iostream>
#include <string>

using namespace std;

void menuLocais() {
    int opcao;
    do {
        cout << "\n--- CRUD de Locais ---\n";
        cout << "1 - Cadastrar local\n";
        cout << "2 - Listar locais\n";
        cout << "3 - Atualizar local\n";
        cout << "4 - Excluir local\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "Escolha: ";
        cin >> opcao;

        string nome, novoNome;
        float x, y;

        switch (opcao) {
            case 1:
                cout << "Nome: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Coordenadas X Y: ";
                cin >> x >> y;
                cadastrarLocal(nome, x, y);
                break;
            case 2:
                listarLocais();
                break;
            case 3:
                cout << "Nome antigo: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Novo nome: ";
                getline(cin, novoNome);
                cout << "Novas coordenadas X Y: ";
                cin >> x >> y;
                atualizarLocal(nome, novoNome, x, y);
                break;
            case 4:
                cout << "Nome do local: ";
                cin.ignore();
                getline(cin, nome);
                excluirLocal(nome);
                break;
        }
    } while (opcao != 0);
}

void menuVeiculos() {
    int opcao;
    do {
        cout << "\n--- CRUD de Veiculos ---\n";
        cout << "1 - Cadastrar veiculo\n";
        cout << "2 - Listar veiculos\n";
        cout << "3 - Atualizar veiculo\n";
        cout << "4 - Excluir veiculo\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "Escolha: ";
        cin >> opcao;

        string placa, modelo, status, local;

        switch (opcao) {
            case 1:
                cout << "Placa: ";
                cin.ignore();
                getline(cin, placa);
                cout << "Modelo: ";
                getline(cin, modelo);
                cout << "Status: ";
                getline(cin, status);
                cout << "Local atual: ";
                getline(cin, local);
                cadastrarVeiculo(placa, modelo, status, local);
                break;
            case 2:
                listarVeiculos();
                break;
            case 3:
                cout << "Placa: ";
                cin.ignore();
                getline(cin, placa);
                cout << "Novo modelo: ";
                getline(cin, modelo);
                cout << "Novo status: ";
                getline(cin, status);
                cout << "Novo local: ";
                getline(cin, local);
                atualizarVeiculo(placa, modelo, status, local);
                break;
            case 4:
                cout << "Placa: ";
                cin.ignore();
                getline(cin, placa);
                excluirVeiculo(placa);
                break;
        }
    } while (opcao != 0);
}

void menuPedidos() {
    int opcao;
    static int proximoIdPedido = 1;

    do {
        cout << "\n--- CRUD de Pedidos ---\n";
        cout << "1 - Cadastrar pedido\n";
        cout << "2 - Listar pedidos\n";
        cout << "3 - Atualizar pedido\n";
        cout << "4 - Excluir pedido\n";
        cout << "5 - Associar pedido a veiculo\n";
        cout << "6 - Finalizar entrega\n";
        cout << "    (Após a simulação da entrega, o status do veículo será alterado para 'disponível' e o local atualizado para o destino do pedido)\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "Escolha: ";
        cin >> opcao;

        int id;
        string origem, destino, placa;
        float peso;

        switch (opcao) {
            case 1:
                cout << "Origem: ";
                cin.ignore();
                getline(cin, origem);
                cout << "Destino: ";
                getline(cin, destino);
                cout << "Peso: ";
                cin >> peso;
                cadastrarPedido(proximoIdPedido++, origem, destino, peso);
                break;
            case 2:
                listarPedidos();
                break;
            case 3:
                cout << "ID do pedido: ";
                cin >> id;
                cin.ignore();
                cout << "Nova origem: ";
                getline(cin, origem);
                cout << "Novo destino: ";
                getline(cin, destino);
                cout << "Novo peso: ";
                cin >> peso;
                atualizarPedido(id, origem, destino, peso);
                break;
            case 4:
                cout << "ID do pedido: ";
                cin >> id;
                excluirPedido(id);
                break;
            case 5:
                cout << "ID do pedido: ";
                cin >> id;
                cin.ignore();
                cout << "Placa do veiculo: ";
                getline(cin, placa);
                associarPedidoVeiculo(id, placa);
                break;
            case 6:
                cout << "ID do pedido: ";
                cin >> id;
                cin.ignore();
                cout << "Placa do veiculo: ";
                getline(cin, placa);
                finalizarEntrega(id, placa);
                cout << "Após a entrega, o status do veículo será 'disponível' e o local atualizado para o destino do pedido.\n";
                break;
        }
    } while (opcao != 0);
}
