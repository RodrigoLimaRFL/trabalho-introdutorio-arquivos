#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerencia-arquivo.h"
#include "lista.h"

struct dados {
    int id;
    int idade;
    char *nome_jogador;
    char *nacionalidade;
    char *nomeClube;
};

void lerCsv(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }

    char linha[1090];
    int i = 0;
    while (fgets(linha, 100, arquivo) != NULL && i < 7) {
        int id;
        char *idString = strtok(linha, ",");
        if (idString == NULL|| strcmp(idString, "") == 0 || strcmp(idString, "\0") == 0 ) {
            id = -1;
        }
        else {
            id = atoi(idString);
        }

        int idade;
        char *idadeString = strtok(NULL, ",");
        if (idadeString == NULL || strcmp(idadeString, "") == 0 || strcmp(idString, "\r") == 0 ) {
            idade = -1;
        } else {
            idade = atoi(idadeString);
        }

        char *nome_jogador = strtok(NULL, ",");
        if (nome_jogador == NULL || strcmp(nome_jogador, "") == 0) {
            nome_jogador = "$$$";
        }

        char *nacionalidade = strtok(NULL, ",");
        if (nacionalidade == NULL || strcmp(nacionalidade, "") == 0) {
            nacionalidade = "$$$";
        }

        char *nomeClube = strtok(NULL, ",");
        if (nomeClube == NULL || strcmp(nomeClube, "") == 0) {
            nomeClube = "$$$";
        }

        printf("ID: %d\n", id);
        printf("Idade: %d\n", idade);
        printf("Nome: %s\n", nome_jogador);
        printf("Nacionalidade: %s\n", nacionalidade);
        printf("Clube: %s\n", nomeClube);
        printf("\n");
        i++;
    }

    fclose(arquivo);
}

void teste() {
    DADOS *dados = (DADOS *) malloc(sizeof(DADOS));
    char *linha = "1, 33, Messi, Argentina, Barcelona";
    lerLinha(linha, dados);
    printf("ID: %d\n", dados->id);
    printf("Idade: %d\n", dados->idade);
    printf("Nome: %s\n", dados->nome_jogador);
    printf("Nacionalidade: %s\n", dados->nacionalidade);
    printf("Clube: %s\n", dados->nomeClube);
}

void lerLinha(char *linha, DADOS *dados) {
    int contadores[5];
    int i = 0;
    int j = 0;
    int offset = 0;
    while(linha[i] != '\n' && linha[i] != '\0') {
        if (linha[i] == ',') {
            contadores[j] = i - offset;
            offset = i + 1;
            j++;
        }
        i++;
    }
    contadores[j] = i - offset;
    char *id = (char *) malloc((contadores[0] + 1) * sizeof(char));
    char *idade = (char *) malloc((contadores[1] + 1) * sizeof(char));
    char *nome_jogador = (char *) malloc((contadores[2] + 1) * sizeof(char));
    char *nacionalidade = (char *) malloc((contadores[3] + 1) * sizeof(char));
    char *nomeClube = (char *) malloc((contadores[4] + 1) * sizeof(char));
    i = 0;
    for(j = 0; j < contadores[0]; i++) {
        id[j] = linha[i];
        j++;
    }
    id[contadores[0]] = '\0';
    i++;
    for(j = 0; j < contadores[1]; j++) {
        idade[j] = linha[i];
        i++;
    }
    idade[contadores[1]] = '\0';
    i++;
    for(j = 0; j < contadores[2]; j++) {
        nome_jogador[j] = linha[i];
        i++;
    }
    nome_jogador[contadores[2]] = '\0';
    i++;
    for(j = 0; j < contadores[3]; j++) {
        nacionalidade[j] = linha[i];
        i++;
    }
    nacionalidade[contadores[3]] = '\0';
    i++;
    for(j = 0; j < contadores[4]; j++) {
        nomeClube[j] = linha[i];
        i++;
    }
    nomeClube[contadores[4]] = '\0';
    dados->id = atoi(id);
    dados->idade = atoi(idade);
    dados->nome_jogador = nome_jogador;
    dados->nacionalidade = nacionalidade;
    dados->nomeClube = nomeClube;
}