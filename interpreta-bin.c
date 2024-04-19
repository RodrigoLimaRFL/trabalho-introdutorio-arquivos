#include "interpreta-bin.h"

void lerRegistroFromBin(FILE *file, REGISTRO *registro)
{
    char removido;
    fread(&removido, sizeof(char), 1, file);
    set_removido(registro, removido);

    int tamanhoRegistro;
    fread(&tamanhoRegistro, sizeof(int), 1, file);
    set_tamanhoRegistro(registro, tamanhoRegistro);

    long prox;
    fread(&prox, sizeof(long), 1, file);
    set_prox(registro, prox);

    int id;
    fread(&id, sizeof(int), 1, file);
    set_id(registro, id);

    int idade;
    fread(&idade, sizeof(int), 1, file);
    set_idade(registro, idade);

    int tamNomeJogador;
    fread(&tamNomeJogador, sizeof(int), 1, file);
    set_tamNomeJogador(registro, tamNomeJogador);

    char *nomeJogador = (char *)malloc(tamNomeJogador);
    fread(nomeJogador, sizeof(char), tamNomeJogador, file);
    set_nomeJogador(registro, nomeJogador);

    int tamNacionalidade;
    fread(&tamNacionalidade, sizeof(int), 1, file);
    set_tamNacionalidade(registro, tamNacionalidade);

    char *nacionalidade = (char *)malloc(tamNacionalidade);
    fread(nacionalidade, sizeof(char), tamNacionalidade, file);
    set_nacionalidade(registro, nacionalidade);

    int tamNomeClube;
    fread(&tamNomeClube, sizeof(int), 1, file);
    set_tamNomeClube(registro, tamNomeClube);

    char *nomeClube = (char *)malloc(tamNomeClube);
    fread(nomeClube, sizeof(char), tamNomeClube, file);
    set_nomeClube(registro, nomeClube);
}

LISTA *getRegistrosFromBin(char *filePath)
{
    FILE *file = fopen(filePath, "rb");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", filePath);
        return NULL;
    }

    int i = 0;
    LISTA *lista = criarLista();
    while (1)
    {
        REGISTRO *registro = criarRegistroNulo();
        lerRegistroFromBin(file, registro);
        if (feof(file))
        {
            break;
        }
        inserirRegistro(lista, registro);
    }

    fclose(file);
    return lista;
}