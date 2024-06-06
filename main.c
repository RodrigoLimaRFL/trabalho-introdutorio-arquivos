#include <stdio.h>

#include "gerencia-arquivo.h"
#include "escreveBin.h"
#include "interpreta-bin.h"
#include "cabecalho.h"
#include "funcoes_fornecidas.h"
#include "criarIndice.h"
#include "percorreCsv.h"
#include "inserirDado.h"
#include "removidos.h"

int main() {
    char operacao[2];
    scanf("%s", operacao); // lê qual operação que vai realizar

    FILE *file;
    
    if(strcmp(operacao, "1") == 0)
    {
        // Ler Csv e escrever binario
        char arquivoCsv[50];
        scanf("%s", arquivoCsv); // lê o nome do arquivo csv
        char arquivoBin[50];
        scanf("%s", arquivoBin); // lê o nome do arquivo binário

        lerCsvEscreveBin(arquivoCsv, arquivoBin);

        binarioNaTela(arquivoBin);
    }
    else if (strcmp(operacao, "2") == 0)
    {
        // Ler binario
        char arquivoBin[50];
        scanf("%s", arquivoBin);

        imprimeRegistrosFromBin(arquivoBin); // armazena os registros do arquivo binário na lista
    }
    else if (strcmp(operacao, "3") == 0)
    {
        // Buscar
        char arquivoBin[50];
        scanf("%s", arquivoBin);

        imprimeRegistrosBuscados(arquivoBin);
    }
    else if(strcmp(operacao, "4") == 0)
    {
        // adicionar nome do indice
        // Ler binario
        char arquivoBin[50];
        scanf("%s", arquivoBin);
        char arquivoIndice[50];
        scanf("%s", arquivoIndice);

        file = fopen(arquivoBin, "wb+"); // verifica se ocorreu um erro ao abrir o arquivo no modo leitura e escrita
        if (file == NULL)
        {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

        if(lerBinCriarIndice(file, arquivoIndice))
        {
            binarioNaTela(arquivoIndice);
        }
    } else if(strcmp(operacao, "5") == 0)
    {
        char arquivoBin[50];
        scanf("%s", arquivoBin);

        char arquivoIndice[50];
        scanf("%s", arquivoIndice);

        file = fopen(arquivoBin, "rb+");
        if (file == NULL) // verifica se ocorreu um erro ao abrir o arquivo no modo leitura e escrita
        {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

        FILE *fileIndice = lerBinCriarIndice(file, arquivoIndice);
        
        printf("chegou\n");
        REMOVIDOS *removidos = criarListaRemovidos(file);
        printf("chegouuuuuuu\n");

        LISTA_INDICE *listaIndices = criarListaIndice();
        carregarIndice(listaIndices, fileIndice);


        removerRegistrosBuscados(file, removidos, listaIndices);

        binarioNaTela(arquivoBin);
        binarioNaTela(arquivoIndice);
    }
    else if(strcmp(operacao, "6") == 0)
    {
        char arquivoBin[50];
        scanf("%s", arquivoBin);

        char arquivoIndice[50];
        scanf("%s", arquivoIndice);

        int numOperacoes;

        scanf("%d", &numOperacoes);

        for(int i = 0; i < numOperacoes; i++)
        {
            printf("a\n ");
            inserirNovoDado(arquivoBin, arquivoIndice);
            printf("b\n");
        }

        binarioNaTela(arquivoBin);
        binarioNaTela(arquivoIndice);
    }
    else // se a operação for diferente de 1, 2 ou 3, imprime, imprime que a operação é inválida
    {
        printf("Operacao invalida\n");
    }

    return 0;
}