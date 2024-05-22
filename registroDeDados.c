#include "registroDeDados.h"

struct _registro_dados {
    int index;
    long long int byteOffset;
};

struct _indice {
    char status;
    int quantidade; // nao insere no arquivo
    REGISTRO_DADOS *dados;
};

#pragma region Criar e Apagar

REGISTRO_DADOS *criarRegistroDados() {
    REGISTRO_DADOS *registro = (REGISTRO_DADOS *) malloc(sizeof(REGISTRO_DADOS));
    if(!registro)
        return NULL;
    registro->index = -1;
    registro->byteOffset = -1;
    return registro;
}

INDICE *criarIndice() {
    INDICE *indice = (INDICE *) malloc(sizeof(INDICE));
    if(!indice)
        return NULL;
    indice->status = '1';
    indice->dados = NULL;
    return indice;
}

void apagarRegistroDados(REGISTRO_DADOS *registro) {
    free(registro);
}

void apagarIndice(INDICE *indice) {
    for(int i = 0; i < indice->quantidade; i++)
        apagarRegistroDados(&indice->dados[i]);
    free(indice->dados);
    free(indice);
}

#pragma endregion

#pragma region Getters and Setters

void setStatus(INDICE *indice, char status) {
    indice->status = status;
}

void setQuantidade(INDICE *indice, int quantidade) {
    indice->quantidade = quantidade;
}

void setDados(INDICE *indice, REGISTRO_DADOS *dados) {
    indice->dados = dados;
}

char getStatus(INDICE *indice) {
    return indice->status;
}

int getQuantidade(INDICE *indice) {
    return indice->quantidade;
}

REGISTRO_DADOS *getDados(INDICE *indice) {
    return indice->dados;
}

void setIndex(REGISTRO_DADOS *registro, int index) {
    registro->index = index;
}

void setByteOffset(REGISTRO_DADOS *registro, long long int byteOffset) {
    registro->byteOffset = byteOffset;
}

int getIndex(REGISTRO_DADOS *registro) {
    return registro->index;
}

long long int getByteOffset(REGISTRO_DADOS *registro) {
    return registro->byteOffset;
}

#pragma endregion

