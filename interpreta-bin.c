#include "interpreta-bin.h"
#include "cabecalho.h"

void lerCabecalhoFromBin(FILE *file, CABECALHO *cabecalho)
{
    char status;
    fread(&status, sizeof(char), 1, file);
    setStatus(cabecalho, status);

    long topo;
    fread(&topo, sizeof(long), 1, file);
    setTopo(cabecalho, topo);

    long proxByteOffset;
    fread(&proxByteOffset, sizeof(long), 1, file);
    setProxByteOffset(cabecalho, proxByteOffset);

    int nroRegArq;
    fread(&nroRegArq, sizeof(int), 1, file);
    setNroRegArq(cabecalho, nroRegArq);

    int nroRem;
    fread(&nroRem, sizeof(int), 1, file);
    setNroRem(cabecalho, nroRem);
}

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

CABECALHO *getCabecalhoFromBin(char *filePath)
{
    FILE *file = fopen(filePath, "rb");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", filePath);
        return NULL;
    }

    CABECALHO *cabecalho = criarCabecalho();
    lerCabecalhoFromBin(file, cabecalho);

    fclose(file);
    return cabecalho;
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

    CABECALHO *cabecalho = criarCabecalho();
    lerCabecalhoFromBin(file, cabecalho);

    long byteOffset = getProxByteOffset(cabecalho);
    int numRegistros = getNroRegArq(cabecalho);
    byteOffset = 25;
    
    for (i = 0; i < 1000; i++)
    {
        fseek(file, byteOffset, SEEK_SET);
        REGISTRO *registro = criarRegistroNulo();
        lerRegistroFromBin(file, registro);
        byteOffset += get_tamanhoRegistro(registro);
        adicionarRegistro(lista, registro);
    }

    fclose(file);
    return lista;
}