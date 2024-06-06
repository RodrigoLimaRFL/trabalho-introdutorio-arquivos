#include "inserirDado.h"

// escrevendo o ultimo em todos
void inserirNovoDado(char *arquivoBinario, char *arquivoIndice, int numOperacoes)
{
    FILE *arquivoBin = fopen(arquivoBinario, "rb+");
    FILE *arquivoInd = fopen(arquivoIndice, "rb+");

    if (arquivoBin == NULL || arquivoInd == NULL)
    {
        return;
    }
    CABECALHO *cabecalho = getCabecalhoFromBin(arquivoBin);

    if(getStatus(cabecalho) == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    LISTA_INDICE *lista = criarListaIndice();
    carregarIndice(lista, arquivoInd);

    REMOVIDOS *removidos = criarListaRemovidos(arquivoBin);

    REGISTRO **registros = malloc(sizeof(REGISTRO *) * numOperacoes);

    int id;
    char idadeStr[10];
    char **nomeJogador = malloc(sizeof(char*) * numOperacoes);
    char **nacionalidade = malloc(sizeof(char*) * numOperacoes);
    char **nomeClube = malloc(sizeof(char*) * numOperacoes);

    for(int i = 0; i < numOperacoes; i++)
    {
        for(int j = 0; j < numOperacoes; j++)
        {
            nomeJogador[j] = malloc(sizeof(char) * 50);
            nacionalidade[j] = malloc(sizeof(char) * 50);
            nomeClube[j] = malloc(sizeof(char) * 50);
        }

        // le o input do usuario
        scanf("%i", &id);
        scan_quote_string(idadeStr);
        scan_quote_string(nomeJogador[i]);
        scan_quote_string(nacionalidade[i]);
        scan_quote_string(nomeClube[i]);
        REGISTRO_INDICE *registroIndice = buscarRegistroIndice(lista, id);

        if(registroIndice != NULL)
        {
            printf("Registro já existe\n");
            //apagarCabecalho(cabecalho);
            // apagarListaIndice(lista); dando double free pq a lista removidos usa o mesmo registro
            // criar funcao pra apagar lista removidos
            continue;
        }

        int idade = -1;

        if(strcmp(idadeStr, "NULO") == 0 || strcmp(idadeStr, "") == 0)
        {
            idade = -1;
        }
        else
        {
            idade = atoi(idadeStr);
        }

        if(strcmp(nomeJogador[i], "NULO") == 0 || strcmp(nomeJogador[i], "") == 0)
        {
            strcpy(nomeJogador[i], "");
        }

        if(strcmp(nacionalidade[i], "NULO") == 0 || strcmp(nacionalidade[i], "") == 0)
        {
            strcpy(nacionalidade[i], "");
        }

        if(strcmp(nomeClube[i], "NULO") == 0 || strcmp(nomeClube[i], "") == 0)
        {
            strcpy(nomeClube[i], "");
        }

        registros[i] = criarRegistro('0', 
                                     33 + strlen(nomeJogador[i]) + strlen(nomeClube[i]) + strlen(nacionalidade[i]), 
                                     -1,
                                     id,
                                     idade,
                                     strlen(nomeJogador[i]),
                                     nomeJogador[i],
                                     strlen(nacionalidade[i]),
                                     nacionalidade[i], 
                                     strlen(nomeClube[i]),
                                     nomeClube[i]);
    }


    cabecalho = getCabecalhoFromBin(arquivoBin);

    long long int *byteOffsets = getBestFitArrayRegistros(removidos, registros, numOperacoes, arquivoBin);
    int tamanhoRegistroAtual = 0;

    for(int i = 0; i < numOperacoes; i++)
    {
        printf("\n");
        printf("tamanhoRegistro: %d\n", get_tamanhoRegistro(registros[i]));
        printf("byteOffset: %lld\n", byteOffsets[i]);
        imprimeRegistro(registros[i]);

        // erro aqui
        if(byteOffsets[i] == -1)
        {
            tamanhoRegistroAtual = 0;
            fseek(arquivoBin, 0, SEEK_END);
            byteOffsets[i] = ftell(arquivoBin);
        }
        else
        {
            tamanhoRegistroAtual = get_tamanhoRegistro(lerRegistroFromBin(byteOffsets[i], arquivoBin));
            printf("tamanhoRegistroAtual: %d\n", tamanhoRegistroAtual);
        }

        printf("aqui\n");

        set_prox(registros[i], -1);

        // escrevendo arquivo
        setStatus(cabecalho, '0');
        writeStatusCabecalho(cabecalho, arquivoBin);

        // escreve os dados do registro no arquivoBin
        escreverRegistro(registros[i], get_tamanhoRegistro(registros[i]), tamanhoRegistroAtual, arquivoBin);

        printf("aqui\n");

        if(tamanhoRegistroAtual != 0)
        {
            set_tamanhoRegistro(registros[i], tamanhoRegistroAtual);
        }

        // terminou de escrever o arquivo
        setStatus(cabecalho, '1');
        writeStatusCabecalho(cabecalho, arquivoBin);

        // cria o registro de indice adequado
        REGISTRO_INDICE *registroIndice = criarRegistroIndice();
        setIndexRegistroIndice(registroIndice, get_id(registros[i]));
        setByteOffsetRegistroIndice(registroIndice, byteOffsets[i]);

        long long int byteOffsetArquivoIndice = buscarPosicaoArquivoIndice(get_id(registros[i]), arquivoInd);

        insertInPosicaoBinIndice(registroIndice, arquivoInd, byteOffsetArquivoIndice);
    }

    free(nomeJogador);
    free(nacionalidade);
    free(nomeClube);

    apagarCabecalho(cabecalho);
    // apagarListaIndice(lista); dando double free pq a lista removidos usa o mesmo registro
    // criar funcao pra apagar lista removidos

    fclose(arquivoBin);
    fclose(arquivoInd);
}