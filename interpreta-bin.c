#include "interpreta-bin.h"
#include "cabecalho.h"

void lerCabecalhoFromBin(FILE *file, CABECALHO *cabecalho)
{
    char status;
    fread(&status, sizeof(char), 1, file);
    setStatus(cabecalho, status);

    long long int topo;
    fread(&topo, sizeof(long long int), 1, file);
    setTopo(cabecalho, topo);

    long long int proxByteOffset;
    fread(&proxByteOffset, sizeof(long long int), 1, file);
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

    long long int prox;
    fread(&prox, sizeof(long long int), 1, file);
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
    for(int i = 0; i < tamNomeJogador; i++)
    {
        fread(&nomeJogador[i], sizeof(char), 1, file);
    }
    set_nomeJogador(registro, nomeJogador);

    int tamNacionalidade;
    fread(&tamNacionalidade, sizeof(int), 1, file);
    set_tamNacionalidade(registro, tamNacionalidade);

    char *nacionalidade = (char *)malloc(tamNacionalidade);
    for(int i = 0; i < tamNacionalidade; i++)
    {
        fread(&nacionalidade[i], sizeof(char), 1, file);
    }
    set_nacionalidade(registro, nacionalidade);

    int tamNomeClube;
    fread(&tamNomeClube, sizeof(int), 1, file);
    set_tamNomeClube(registro, tamNomeClube);

    char *nomeClube = (char *)malloc(tamNomeClube);
    for(int i = 0; i < tamNomeClube; i++)
    {
        fread(&nomeClube[i], sizeof(char), 1, file);
    }
    set_nomeClube(registro, nomeClube);
}

CABECALHO *getCabecalhoFromBin(char *filePath)
{
    FILE *file = fopen(filePath, "rb");
    if (file == NULL)
    {
        printf("Falha no processamento do arquivo.");
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
        printf("Falha no processamento do arquivo.");
        return NULL;
    }

    int i = 0;
    LISTA *lista = criarLista();

    CABECALHO *cabecalho = criarCabecalho();
    lerCabecalhoFromBin(file, cabecalho);

    long long int byteOffset = getProxByteOffset(cabecalho);
    int numRegistros = getNroRegArq(cabecalho) + getNroRem(cabecalho);
    byteOffset = 25;

    if(numRegistros == 0)
    {
        printf("Registro inexistente.\n");
        fclose(file);
        return lista;
    }
    
    for (i = 0; i < numRegistros; i++)
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