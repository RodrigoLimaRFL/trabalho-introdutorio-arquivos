#include "criarIndice.h"

// Função que busca a posição de inserção de um registro no arquivo de índice
// Nao necessita armazenamento na memoria principal, porem eh O(n)
int buscaArquivoIndice(int id, FILE *arquivoInd)
{
    int quantidade;
    int posicao = 1; // primeiro byte apos cabecalho
    fread(&quantidade, sizeof(int), 1, arquivoInd);

    fseek(arquivoInd, posicao, SEEK_SET);

    int index = -1;

    while(fread(&index, sizeof(int), 1, arquivoInd) == 1)
    {
        if(index == id)
        {
            return -1; // indice ja existe
        }
        else if (id < index)
        {
            return posicao; // byte offset do primeiro registro com index maior que id
        }

        posicao = posicao + sizeof(int) + sizeof(long long int); // pula para o proximo registro
        fseek(arquivoInd, posicao, SEEK_SET);
    }

    return posicao; // nao existe nenhum registro com index maior que id
}

// Função que insere um registro no arquivo de índice na posição posicao
int insertInPosicaoBin (REGISTRO_INDICE *registro, FILE *arquivoInd, long long int posicao)
{
    fseek(arquivoInd, 0, SEEK_END);
    long long int bytesToMove = ftell(arquivoInd) - posicao;

    char *buffer = (char *) malloc(bytesToMove);
    if (buffer == NULL)
    {
        printf("Erro ao alocar memoria\n");
        return 0;
    }

    fseek(arquivoInd, posicao, SEEK_SET);
    fread(buffer, bytesToMove, 1, arquivoInd); // le todos os bytes no buffer

    fseek(arquivoInd, posicao + sizeof(int) + sizeof(long long int), SEEK_SET);

    fwrite(buffer, bytesToMove, 1, arquivoInd); // reescreve o buffer no arquivo separando posicao pro novo registro

    fseek(arquivoInd, posicao, SEEK_SET);

    // escreve o novo registro
    int index = getIndexRegistroIndice(registro);
    long long int byteOffset = getByteOffsetRegistroIndice(registro);
    fwrite(&index, sizeof(int), 1, arquivoInd);
    fwrite(&byteOffset, sizeof(long long int), 1, arquivoInd);

    free(buffer);

    return 1;
}

void imprimirRegistrosIndice(FILE *arquivoIndice)
{
    fseek(arquivoIndice, 1, SEEK_SET);
    
    int index = -1;
    long long int byteOffset = -1;

    while(fread(&index, sizeof(int), 1, arquivoIndice) == 1)
    {
        fread(&byteOffset, sizeof(long long int), 1, arquivoIndice);
    }
}

bool lerBinCriarIndice(char *arquivoBin, char *arquivoIndice)
{
    FILE *arquivoBinario = fopen(arquivoBin, "rb");
    if(arquivoBinario == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return false;
    }

    FILE *arquivoInd = fopen(arquivoIndice, "wb+");
    if (arquivoInd == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return false;
    }
    
    CABECALHO *cabecalho = getCabecalhoFromBin(arquivoBinario);

    if (getStatus(cabecalho) == '0')
    {
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivoBinario); // fecha o arquivo
        fclose(arquivoInd);
        return false;
    }

    char status = '0';
    fwrite(&status, sizeof(char), 1, arquivoInd);

    long long int posicao = 25;

    REGISTRO_INDICE *registroIndice = criarRegistroIndice();

    int quantidade = getNroRegArq(cabecalho) + getNroRem(cabecalho);

    for(int i = 0; i < quantidade; i++)
    {
        REGISTRO *registro = lerRegistroFromBin(posicao, arquivoBinario);

        if(get_removido(registro) == '1')
        {
            posicao += get_tamanhoRegistro(registro);
            liberarRegistro(registro);
            continue;
        }

        setIndexRegistroIndice(registroIndice, get_id(registro));
        setByteOffsetRegistroIndice(registroIndice, posicao);

        int posicaoInsercao = buscaArquivoIndice(get_id(registro), arquivoInd);
        insertInPosicaoBin(registroIndice, arquivoInd, posicaoInsercao);

        posicao += get_tamanhoRegistro(registro);
        liberarRegistro(registro);
    }

    apagarRegistroIndice(registroIndice);

    status = '1';
    fseek(arquivoInd, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, arquivoInd);

    //imprimirRegistrosIndice(arquivoInd);
    
    fclose(arquivoBinario);
    fclose(arquivoInd);

    return true;
}
/*
// Adicionar byteoffset e imprimir pra bin
INDICE *criarArquivoDeIndice(LISTA *listaRegistros, CABECALHO *cabecalho)
{
    int byteOffset = 34; //cabecalho tem 33 bytes -> primeiro byte eh 34
    INDICE *indice = criarIndice();
    setStatusIndice(indice, '1');
    for(int i = 0; i < getTamanho(listaRegistros); i++)
    {
        REGISTRO *registro = getRegistro(listaRegistros, i);
        if(get_removido(registro) == '0')
        {
            REGISTRO_DADOS *registroDados = criarRegistroDados();
            setIndexRegistroIndice(registroDados, get_id(registro));
            setByteOffsetRegistroIndice(registroDados, byteOffset);
            insertRegistroIndice(indice, registroDados);
            byteOffset += get_tamanhoRegistro(registro);
        }
    }
    setStatusIndice(indice, '0');

    return indice;
}

void escreveIndiceBinario(INDICE *indice, char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if(arquivo == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    char status = getStatusIndice(indice);
    fwrite(&status, sizeof(char), 1, arquivo);

    int quantidade = getQuantidadeIndice(indice);
    fwrite(&quantidade, sizeof(int), 1, arquivo);

    REGISTRO_DADOS **dados = getDadosIndice(indice);

    printf("%d \n", getIndexRegistroIndice(dados[0]));

    for(int i = 0; i < quantidade; i++)
    {
        //fwrite(getIndexRegistroIndice(dados), sizeof(int), 1, arquivo);
        //fwrite(getByteOffsetRegistroIndice(dados[i]), sizeof(long long int), 1, arquivo);
    }

    //apagarIndice(indice);
    fclose(arquivo);
}*/