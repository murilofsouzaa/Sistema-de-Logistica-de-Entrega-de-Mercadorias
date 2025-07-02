#include <iostream>
#include <locale>
#include "Menu.hpp"
#include "Veiculo.hpp"
#include "Local.hpp"      
#include "Pedido.hpp"

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

using namespace std;

int main() {
    std::setlocale(LC_ALL, "");

    int opcao;

    // Inserir dados de teste automaticamente ao iniciar
    inserirDadosTeste();

    do {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1 - Gerenciar Locais\n";
        cout << "2 - Gerenciar Veiculos\n";
        cout << "3 - Gerenciar Pedidos\n";
        cout << "4 - Fazer Backup dos Dados\n";
        cout << "5 - Restaurar Dados do Backup\n";
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
                backupDados();
                break;
            case 5:
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