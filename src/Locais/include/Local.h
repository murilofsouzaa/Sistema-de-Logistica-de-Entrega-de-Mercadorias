#ifndef LOCAL_HPP
#define LOCAL_HPP

#include <string>

// Struct Local com seus atributos
struct Local {
    std::string nome;
    float x;
    float y;
};

// Protótipos das funções para manipular locais

// Cadastra um novo local (retorna true se sucesso)
bool cadastrarLocal(const std::string& nome, float x, float y);

// Lista todos os locais cadastrados
void listarLocais();

// Atualiza um local identificado pelo nome antigo
bool atualizarLocal(const std::string& nomeAntigo, const std::string& nomeNovo, float novoX, float novoY);

// Exclui um local pelo nome
bool excluirLocal(const std::string& nome);

#endif // LOCAL_HPP
