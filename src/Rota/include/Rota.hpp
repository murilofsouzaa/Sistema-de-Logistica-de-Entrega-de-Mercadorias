#ifndef ROTA_HPP
#define ROTA_HPP

#include <vector>
#include <string>

class Local; 

// Função que calcula a rota ótima (lista de nomes dos locais) dado uma lista de nomes de locais.
std::vector<std::string> calcularRotaEntrega(const std::vector<std::string>& nomesLocais);

#endif 
