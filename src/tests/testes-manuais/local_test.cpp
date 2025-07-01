#include <iostream>
#include "../../Local/include/Local.hpp"

int main() {
    Local l1;
    std::cout << "Esperado: nome vazio, x=0, y=0\n";
    std::cout << "Obtido: " << l1.getNome() << ", x =" << l1.getX() << ", y=" << l1.getY() << "\n\n";

    Local l2("Padaria", 12.5f, 8.0f);
    std::cout << "Esperado: nome = Padaria, x = 12.5, y = 8\n";
    std::cout << "Obtido: " << l2.getNome() << ", x=" << l2.getX() << ", y=" << l2.getY() << "\n\n";

    l1.setNome("Farmacia");
    l1.setCoordenadas(3.0f, 4.0f);
    std::cout << "Esperado: nome=Farmacia, x=3, y=4\n";
    std::cout << "Obtido: " << l1.getNome() << ", x=" << l1.getX() << ", y=" << l1.getY() << "\n\n";

    std::cout << "Teste do metodo exibir:\n";
    l1.exibir();
    l2.exibir();

    float dist = calcularDistanciaEntreLocais(l1, l2);
    std::cout << "\nDistancia entre Farmacia e Padaria: " << dist << "\n";

    return 0;
}
