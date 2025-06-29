#include "include/Local.hpp"
#include <iostream>

#define MAX_LOCAIS 100

static Local locais[MAX_LOCAIS];
static int qtdLocais = 0;


Local::Local() : nome(""), x(0), y(0) {}

Local::Local(const std::string& nome, float x, float y)
    : nome(nome), x(x), y(y) {}

std::string Local::getNome() const {
    return nome;
}

float Local::getX() const {
    return x;
}

float Local::getY() const {
    return y;
}

void Local::setNome(const std::string& novoNome) {
    nome = novoNome;
}

void Local::setCoordenadas(float novoX, float novoY) {
    x = novoX;
    y = novoY;
}

void Local::exibir() const {
    std::cout << "Nome: " << nome << " (X: " << x << ", Y: " << y << ")\n";
}


bool cadastrarLocal(const std::string& nome, float x, float y) {
    if (qtdLocais >= MAX_LOCAIS) {
        std::cout << "Limite de locais atingido!\n";
        return false;
    }

    for (int i = 0; i < qtdLocais; i++) {
        if (locais[i].getNome() == nome) {
            std::cout << "Erro: local com esse nome já existe.\n";
            return false;
        }
    }

    locais[qtdLocais] = Local(nome, x, y);
    qtdLocais++;

    std::cout << "Local cadastrado com sucesso!\n";
    return true;
}

void listarLocais() {
    if (qtdLocais == 0) {
        std::cout << "Nenhum local cadastrado.\n";
        return;
    }

    std::cout << "Lista de locais:\n";
    for (int i = 0; i < qtdLocais; i++) {
        std::cout << i + 1 << ". ";
        locais[i].exibir();
    }
}

bool atualizarLocal(const std::string& nomeAntigo, const std::string& nomeNovo, float novoX, float novoY) {
    for (int i = 0; i < qtdLocais; i++) {
        if (locais[i].getNome() == nomeAntigo) {
            locais[i].setNome(nomeNovo);
            locais[i].setCoordenadas(novoX, novoY);
            std::cout << "Local atualizado com sucesso!\n";
            return true;
        }
    }
    std::cout << "Local não encontrado.\n";
    return false;
}

bool excluirLocal(const std::string& nome) {
    for (int i = 0; i < qtdLocais; i++) {
        if (locais[i].getNome() == nome) {
            for (int j = i; j < qtdLocais - 1; j++) {
                locais[j] = locais[j + 1];
            }
            qtdLocais--;
            std::cout << "Local excluído com sucesso!\n";
            return true;
        }
    }
    std::cout << "Local não encontrado.\n";
    return false;
}
