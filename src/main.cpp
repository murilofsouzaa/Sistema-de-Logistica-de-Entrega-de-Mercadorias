#include <iostream>
#include <locale>
#include "./Menu/include/Menu.hpp"
#include "./Veiculo/include/Veiculo.hpp"
#include "./Local/include/Local.hpp"      
#include "./Pedido/include/Pedido.hpp"    

using namespace std;

int main() {
    std::setlocale(LC_ALL, "");

    int opcao;

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
