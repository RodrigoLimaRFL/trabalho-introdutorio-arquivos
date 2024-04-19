#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerencia-arquivo.h"
#include "lista.h"
#include "cabecalho.h"

struct dados {
    int id;
    int idade;
    char *nome_jogador;
    char *nacionalidade;
    char *nomeClube;
};

LISTA *lerCsv(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }

    char linha[1090];
    int i = 0;

    LISTA *lista = criarLista();

    while(fgets(linha, 1090, arquivo) != NULL) {
        if (i == 0) {
            i++;
            continue;
        }
        DADOS *dados = (DADOS *) malloc(sizeof(DADOS));
        REGISTRO *registro = getRegistro(lista, i - 1);
        lerLinha(linha, dados);

        registro = criarRegistro('0', 
                                (33 + strlen(dados->nome_jogador) + strlen(dados->nacionalidade) + strlen(dados->nomeClube)), 
                                -1,  
                                dados->id,
                                dados->idade,
                                strlen(dados->nome_jogador), 
                                dados->nome_jogador, 
                                strlen(dados->nacionalidade), 
                                dados->nacionalidade, 
                                strlen(dados->nomeClube), 
                                dados->nomeClube);

        printf("ID: %d\n", get_id(registro));
        printf("Idade: %d\n", get_idade(registro));
        printf("Nome: %s\n", get_nomeJogador(registro));
        printf("Nacionalidade: %s\n", get_nacionalidade(registro));
        printf("Clube: %s\n", get_nomeClube(registro));
        printf("\n");

        adicionarRegistro(lista, registro);

        i++;
    }

    return lista;

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

void escreveBinario(CABECALHO *cabecalho, LISTA *lista, char *binario) {
  FILE *f = fopen(binario, "wb");

  char status = getStatus(cabecalho);
  long topo = getTopo(cabecalho);
  long proxByteOffset = getProxByteOffset(cabecalho);
  int nroRegArq = getNroRegArq(cabecalho);
  int nroRegRem = getNroRem(cabecalho);

  fwrite(&status, 1, 1, f);
  fwrite(&topo, 8, 1, f);
  fwrite(&proxByteOffset, 8, 1, f);
  fwrite(&nroRegArq, 4, 1, f);
  fwrite(&nroRegRem, 4, 1, f);

  for(int i=0; i<getTamanho(lista); i++) {
    int removido = get_removido(getRegistro(lista, i));
    int tamRegistro = get_tamanhoRegistro(getRegistro(lista, i));
    long prox = get_prox(getRegistro(lista, i));
    int id = get_id(getRegistro(lista, i));
    int idade = get_idade(getRegistro(lista, i));
    int tamNomeJogador = get_tamNomeJogador(getRegistro(lista, i));
    char *nomeJogador = get_nomeJogador(getRegistro(lista, i));
    int tamNacionalidade = get_tamNacionalidade(getRegistro(lista, i));
    char *nacionalidade = get_nacionalidade(getRegistro(lista, i));
    int tamNomeClube = get_tamNomeClube(getRegistro(lista, i));
    char *nomeClube = get_nomeClube(getRegistro(lista, i));

    fwrite(&removido, 1, 1, f);
    fwrite(&tamRegistro, 4, 1, f);
    fwrite(&prox, 8, 1, f);
    fwrite(&id, 4, 1, f);
    fwrite(&idade, 4, 1, f);
    fwrite(&tamNomeJogador, 4, 1, f);
    fwrite(nomeJogador, 1, get_tamNomeJogador(getRegistro(lista, i)), f);
    fwrite(&tamNacionalidade, 4, 1, f);
    fwrite(nacionalidade, 1, get_tamNacionalidade(getRegistro(lista, i)), f);
    fwrite(&tamNomeClube, 4, 1, f);
    fwrite(nomeClube, 1, get_tamNomeClube(getRegistro(lista, i)), f);
  }

  fclose(f);
}