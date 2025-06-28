#ifndef LOCAL_HPP
#define LOCAL_HPP

#include <string>

class Local {
private:
    std::string nome;
    float x;
    float y;

public:
    Local();
    Local(const std::string& nome, float x, float y);

    std::string getNome() const;
    float getX() const;
    float getY() const;

    void setNome(const std::string& novoNome);
    void setCoordenadas(float novoX, float novoY);
    void exibir() const;
};

// Funções de gerenciamento de locais
bool cadastrarLocal(const std::string& nome, float x, float y);
void listarLocais();
bool atualizarLocal(const std::string& nomeAntigo, const std::string& nomeNovo, float novoX, float novoY);
bool excluirLocal(const std::string& nome);

#endif
