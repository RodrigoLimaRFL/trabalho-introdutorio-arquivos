#include "indice.h"
#include <stdio.h>
#include <stdlib.h>

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
    indice->quantidade = 0;
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

void setStatusIndice(INDICE *indice, char status) {
    indice->status = status;
}

void setQuantidadeIndice(INDICE *indice, int quantidade) {
    indice->quantidade = quantidade;
}

void setDadosIndice(INDICE *indice, REGISTRO_DADOS *dados) {
    indice->dados = dados;
}

char getStatusIndice(INDICE *indice) {
    return indice->status;
}

int getQuantidadeIndice(INDICE *indice) {
    return indice->quantidade;
}

REGISTRO_DADOS *getDadosIndice(INDICE *indice) {
    return indice->dados;
}

void setIndexRegistroIndice(REGISTRO_DADOS *registro, int index) {
    registro->index = index;
}

void setByteOffsetRegistroIndice(REGISTRO_DADOS *registro, long long int byteOffset) {
    registro->byteOffset = byteOffset;
}

int getIndexRegistroIndice(REGISTRO_DADOS *registro) {
    return registro->index;
}

long long int getByteOffsetRegistroIndice(REGISTRO_DADOS *registro) {
    return registro->byteOffset;
}

#pragma endregion

bool binarySearchIndice(INDICE *indice, int index, int *pos) {
    int inicio = 0;
    int fim = indice->quantidade - 1;
    int meio;
    while(inicio <= fim) {
        meio = (inicio + fim) / 2;
        if(indice->dados[meio].index == index) {
            *pos = meio;
            return true;
        }
        if(indice->dados[meio].index < index)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    *pos = inicio; // Adjusting to ensure pos points to the correct insertion point
    return false;
}

void shiftRegistrosRight(INDICE *indice, int pos) {
    // Allocate more memory to accommodate the new element
    indice->dados = (REGISTRO_DADOS *) realloc(indice->dados, indice->quantidade * sizeof(REGISTRO_DADOS));
    if(!indice->dados)
        return;

    // Shift elements to the right from the end to the position
    for(int i = indice->quantidade - 1; i > pos; i--) {
        indice->dados[i] = indice->dados[i - 1];
    }
}

void insertRegistroIndice(INDICE *indice, REGISTRO_DADOS *registro) {
    int posicao = 0;

    if(indice->quantidade == 0) {
        indice->dados = (REGISTRO_DADOS *) malloc(sizeof(REGISTRO_DADOS));
        if(!indice->dados)
            return;
        indice->dados[0] = *registro;
        indice->quantidade++;
        return;
    }

    if (binarySearchIndice(indice, registro->index, &posicao)) {
        return; // Avoid inserting duplicate indices
    }

    // Increase quantidade after ensuring memory allocation
    indice->quantidade++;
    shiftRegistrosRight(indice, posicao);

    // Insert the new record at the correct position
    indice->dados[posicao] = *registro;

    printf("Indice dado index: %i, byteOffset: %lld\n", indice->dados[posicao].index, indice->dados[posicao].byteOffset);
}

void printRegistrosIndice(INDICE *indice) {
    indice->dados = (REGISTRO_DADOS *) realloc(indice->dados, indice->quantidade * sizeof(REGISTRO_DADOS));
    if(!indice->dados)
        return;
    for(int i = 0; i < indice->quantidade; i++) {
        printf("index: %d, byteOffset: %lld\n", indice->dados[i].index, indice->dados[i].byteOffset);
    }
}