#include "../include/Local.h"
#include <iostream>
#include <vector>

#define MAX_LOCAIS 100

static Local locais[MAX_LOCAIS];
static int qtdLocais = 0;

bool cadastrarLocal(const std::string& nome, float x, float y) {
    if (qtdLocais >= MAX_LOCAIS) {
        std::cout << "Limite de locais atingido!\n";
        return false;
    }

    for (int i = 0; i < qtdLocais; i++) {
        if (locais[i].nome == nome) {
            std::cout << "Erro: local com esse nome ja existe.\n";
            return false;
        }
    }

    locais[qtdLocais].nome = nome;
    locais[qtdLocais].x = x;
    locais[qtdLocais].y = y;
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
        std::cout << i + 1 << ". " << locais[i].nome << " (X: " << locais[i].x << ", Y: " << locais[i].y << ")\n";
    }
}

bool atualizarLocal(const std::string& nomeAntigo, const std::string& nomeNovo, float novoX, float novoY) {
    for (int i = 0; i < qtdLocais; i++) {
        if (locais[i].nome == nomeAntigo) {
            locais[i].nome = nomeNovo;
            locais[i].x = novoX;
            locais[i].y = novoY;
            std::cout << "Local atualizado com sucesso!\n";
            return true;
        }
    }
    std::cout << "Local nao encontrado.\n";
    return false;
}

bool excluirLocal(const std::string& nome) {
    for (int i = 0; i < qtdLocais; i++) {
        if (locais[i].nome == nome) {
            // Move os locais apos o excluido para tras
            for (int j = i; j < qtdLocais - 1; j++) {
                locais[j] = locais[j + 1];
            }
            qtdLocais--;
            std::cout << "Local excluido com sucesso!\n";
            return true;
        }
    }
    std::cout << "Local nao encontrado.\n";
    return false;
}
