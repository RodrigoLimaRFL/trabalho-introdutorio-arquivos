#include "criarIndice.h"

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

    REGISTRO_DADOS *dados = getDadosIndice(indice);

    printf("%d \n", getIndexRegistroIndice(dados));

    for(int i = 0; i < quantidade; i++)
    {
        //fwrite(getIndexRegistroIndice(dados), sizeof(int), 1, arquivo);
        //fwrite(getByteOffsetRegistroIndice(dados[i]), sizeof(long long int), 1, arquivo);
    }

    //apagarIndice(indice);
    fclose(arquivo);
}*/