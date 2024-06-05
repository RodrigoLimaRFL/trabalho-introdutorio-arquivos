#include "inserirDado.h"

void inserirNovoDado(char *arquivoBinario, char *arquivoIndice)
{
    FILE *arquivoBin = fopen(arquivoBinario, "ab+");
    FILE *arquivoInd = fopen(arquivoIndice, "ab+");

    if (arquivoBin == NULL || arquivoInd == NULL)
    {
        return;
    }

    printf("a\n");

    CABECALHO *cabecalho = getCabecalhoFromBin(arquivoBin);

    if(getStatus(cabecalho) == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    printf("b\n");

    LISTA_INDICE *lista = criarListaIndice();
    carregarIndice(lista, arquivoInd);

    printf("c\n");
    REMOVIDOS *removidos = criarListaRemovidos(arquivoBin);
    printf("d\n");

    int id;
    char idadeStr[10];
    char nomeJogador[50];
    char nacionalidade[50];
    char nomeClube[50];

    // le o input do usuario
    scanf("%i", &id);
    scan_quote_string(idadeStr);
    scan_quote_string(nomeJogador);
    scan_quote_string(nacionalidade);
    scan_quote_string(nomeClube);
    REGISTRO_INDICE *registroIndice = buscarRegistroIndice(lista, id);
    if(registroIndice != NULL)
    {
        printf("Registro já existe\n");
        //apagarCabecalho(cabecalho);
        // apagarListaIndice(lista); dando double free pq a lista removidos usa o mesmo registro
        // criar funcao pra apagar lista removidos
        fclose(arquivoBin);
        fclose(arquivoInd);
        printf("a\n");
        return;
    }

    printf("e\n");

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

    // cria um registro com os dados lidos
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

    // busca o best fit para o registro e tira a posição do registro da lista de removidos
    long long int byteOffset = getBestFitAndFreeSpace(removidos, get_tamanhoRegistro(registro)); // erro => pegando worst fit
    printf("tamanhoRegistro: %d\n", get_tamanhoRegistro(registro));
    printf("byteOffset: %lld\n", byteOffset);
    int tamanhoRegistroAntigo = 0;

    if(byteOffset != -1) // se encontrou um registro removido
        tamanhoRegistroAntigo = get_tamanhoRegistro(lerRegistroFromBin(byteOffset, arquivoBin));
    else // se não encontrou um registro removido
    {
        fseek(arquivoBin, 0, SEEK_END);
        byteOffset = ftell(arquivoBin);
    }

    // escrevendo arquivo
    setStatus(cabecalho, '0');

    // escreve os dados do registro no arquivoBin
    escreverRegistro(registro, byteOffset, tamanhoRegistroAntigo, arquivoBin);

    // terminou de escrever o arquivo
    setStatus(cabecalho, '1');

    printf("a\n");

    removerRegistroRemovidoEAtualizarArquivo(removidos, id, arquivoBin);

    printf("b\n");
    
    // cria o registro de indice adequado
    registroIndice = criarRegistroIndice();
    setIndexRegistroIndice(registroIndice, id);
    setByteOffsetRegistroIndice(registroIndice, byteOffset);

    long long int byteOffsetArquivoIndice = buscarPosicaoArquivoIndice(id, arquivoInd);

    insertInPosicaoBinIndice(registroIndice, arquivoInd, byteOffsetArquivoIndice);

    printf("c \n");

    apagarCabecalho(cabecalho);
    // apagarListaIndice(lista); dando double free pq a lista removidos usa o mesmo registro
    // criar funcao pra apagar lista removidos

    fclose(arquivoBin);
    fclose(arquivoInd);
}