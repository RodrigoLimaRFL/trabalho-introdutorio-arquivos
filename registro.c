/*
* Pedro Henrique Ferreira Silva - NUSP: 14677526
* Rodrigo de Freitas Lima - NUSP: 12547510
*/


#include <stdio.h>
#include <stdlib.h>

#include "registro.h"

struct registro {
    char removido;
    int tamanhoRegistro;
    long prox;
    int id;
    int idade;
    int tamNomeJogador;
    char *nomeJogador;
    int tamNacionalidade;
    char *nacionalidade;
    int tamNomeClube;
    char *nomeClube;
};

void imprimirRegistros(REGISTRO **registros)
{
    if(registros[0] == NULL)
    {
        printf("VAZIO\n");
        return;
    }
    for (int i = 0; registros[i] != NULL; i++)
    {
        printf("Nome do jogador: %s\n", get_nomeJogador(registros[i]));
        printf("Nacionalidade do Jogador: %s\n", get_nacionalidade(registros[i]));
        printf("Clube do Jogador: %s\n", get_nomeClube(registros[i]));
        printf("\n");
    }
}

REGISTRO **intersecaoDoisRegistros(REGISTRO **registro1, REGISTRO **registro2)
{
    REGISTRO **intersecao = (REGISTRO **)malloc(0);
    int quantidade = 0;
    for (int i = 0; registro1[i] != NULL; i++)
    {
        for (int j = 0; registro2[j] != NULL; j++)
        {
            if (get_id(registro1[i]) == get_id(registro2[j]))
            {
                intersecao = (REGISTRO **)realloc(intersecao, sizeof(REGISTRO *) * (quantidade + 1));
                intersecao[quantidade] = registro1[i];
                quantidade++;
            }
        }
    }
    intersecao = (REGISTRO **)realloc(intersecao, sizeof(REGISTRO *) * (quantidade + 1));
    intersecao[quantidade] = NULL;
    return intersecao;
}

REGISTRO *criarRegistroNulo()
{
    REGISTRO *registro = (REGISTRO *)malloc(sizeof(REGISTRO));
    registro->removido = '1';
    registro->tamanhoRegistro = 0;
    registro->prox = -1;
    registro->id = -1;
    registro->idade = -1;
    registro->tamNomeJogador = -1;
    registro->nomeJogador = NULL;
    registro->tamNacionalidade = -1;
    registro->nacionalidade = NULL;
    registro->tamNomeClube = -1;
    registro->nomeClube = NULL;
    return registro;
}

REGISTRO *criarRegistro(char removido, int tamanhoRegistro, long prox, int id, int idade, int tamNomeJogador, char *nomeJogador, int tamNacionalidade, char *nacionalidade, int tamNomeClube, char *nomeClube)
{
    REGISTRO *registro = (REGISTRO *)malloc(sizeof(REGISTRO));
    registro->removido = removido;
    registro->tamanhoRegistro = tamanhoRegistro;
    registro->prox = prox;
    registro->id = id;
    registro->idade = idade;
    registro->tamNomeJogador = tamNomeJogador;
    registro->nomeJogador = nomeJogador;
    registro->tamNacionalidade = tamNacionalidade;
    registro->nacionalidade = nacionalidade;
    registro->tamNomeClube = tamNomeClube;
    registro->nomeClube = nomeClube;
    return registro;
}

char get_removido(REGISTRO *registro)
{
    return registro->removido;
}

int get_tamanhoRegistro(REGISTRO *registro)
{
    return registro->tamanhoRegistro;
}

long get_prox(REGISTRO *registro)
{
    return registro->prox;
}

int get_id(REGISTRO *registro)
{
    return registro->id;
}

int get_idade(REGISTRO *registro)
{
    return registro->idade;
}

int get_tamNomeJogador(REGISTRO *registro)
{
    return registro->tamNomeJogador;
}

char *get_nomeJogador(REGISTRO *registro)
{
    return registro->nomeJogador;
}

int get_tamNacionalidade(REGISTRO *registro)
{
    return registro->tamNacionalidade;
}

char *get_nacionalidade(REGISTRO *registro)
{
    return registro->nacionalidade;
}

int get_tamNomeClube(REGISTRO *registro)
{
    return registro->tamNomeClube;
}

char *get_nomeClube(REGISTRO *registro)
{
    return registro->nomeClube;
}
void set_removido(REGISTRO *registro, int removido)
{
    registro->removido = removido;
}

void set_tamanhoRegistro(REGISTRO *registro, int tamanhoRegistro)
{
    registro->tamanhoRegistro = tamanhoRegistro;
}

void set_prox(REGISTRO *registro, long prox)
{
    registro->prox = prox;
}

void set_id(REGISTRO *registro, int id)
{
    registro->id = id;
}

void set_idade(REGISTRO *registro, int idade)
{
    registro->idade = idade;
}

void set_tamNomeJogador(REGISTRO *registro, int tamNomeJogador)
{
    registro->tamNomeJogador = tamNomeJogador;
}

void set_nomeJogador(REGISTRO *registro, char *nomeJogador)
{
    registro->nomeJogador = nomeJogador;
}

void set_tamNacionalidade(REGISTRO *registro, int tamNacionalidade)
{
    registro->tamNacionalidade = tamNacionalidade;
}

void set_nacionalidade(REGISTRO *registro, char *nacionalidade)
{
    registro->nacionalidade = nacionalidade;
}

void set_tamNomeClube(REGISTRO *registro, int tamNomeClube)
{
    registro->tamNomeClube = tamNomeClube;
}

void set_nomeClube(REGISTRO *registro, char *nomeClube)
{
    registro->nomeClube = nomeClube;
}

void liberarRegistro(REGISTRO *registro)
{
    free(registro->nomeJogador);
    free(registro->nacionalidade);
    free(registro->nomeClube);
    free(registro);
}