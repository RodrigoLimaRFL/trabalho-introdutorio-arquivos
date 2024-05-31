#include "inserirDado.h"

bool inserirNovoDado(char *arquivoBinario, char *arquivoIndice)
{
    FILE *arquivoBin = fopen(arquivoBinario, "ab+");
    FILE *arquivoInd = fopen(arquivoIndice, "ab+");

    if (arquivoBin == NULL || arquivoInd == NULL)
    {
        return false;
    }

    LISTA_INDICE *lista = criarListaIndice();
    carregarIndice(lista, arquivoInd);

    int id;
    char idadeStr[10];
    char nomeJogador[50];
    char nacionalidade[50];
    char nomeClube[50];

    scanf("%i", id);
    scan_quote_string(idadeStr);
    scan_quote_string(nomeJogador);
    scan_quote_string(nacionalidade);
    scan_quote_string(nomeClube);

    REGISTRO_INDICE *registroIndice = buscarRegistroIndice(lista, id);
    if(registroIndice != NULL)
    {
        printf("Registro já existe\n");
        apagarRegistroIndice(registroIndice);
        apagarListaIndice(lista);
        return false;
    }

    if(strcmp(idadeStr, "NULO") == 0)
    {
        strcpy(idadeStr, "");
    }

    if(strcmp(nomeJogador, "NULO") == 0)
    {
        strcpy(nomeJogador, "");
    }

    if(strcmp(nacionalidade, "NULO") == 0)
    {
        strcpy(nacionalidade, "");
    }

    if(strcmp(nomeClube, "NULO") == 0)
    {
        strcpy(nomeClube, "");
    }

    REGISTRO *registro = criarRegistro('0', 
                                        33 + strlen(nomeJogador) + strlen(nomeClube) + strlen(nacionalidade), 
                                        -1,
                                        id,
                                        atoi(idadeStr),
                                        strlen(nomeJogador),
                                        nomeJogador,
                                        strlen(nacionalidade),
                                        nacionalidade, 
                                        strlen(nomeClube),
                                        nomeClube);

    registroIndice = criarRegistroIndice();
    setIndexRegistroIndice(registroIndice, id);
}