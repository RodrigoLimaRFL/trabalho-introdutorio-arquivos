#include <stdio.h>

#include "gerencia-arquivo.h"
#include "lista.h"
#include "interpreta-bin.h"
#include "cabecalho.h"
#include "funcoes_fornecidas.h"

int main() {
    char operacao[2];
    scanf("%s", operacao);
    
    if(strcmp(operacao, "1") == 0)
    {
        // Ler Csv e escrever binario
        char arquivoCsv[50];
        scanf("%s", arquivoCsv);
        char arquivoBin[50];
        scanf("%s", arquivoBin);

        CABECALHO *cabecalho = criarCabecalho();
        LISTA *lista = lerCsv(arquivoCsv);
        escreveBinario(cabecalho, lista, arquivoBin);

        binarioNaTela(arquivoBin);
    }
    else if (strcmp(operacao, "2") == 0)
    {
        // Ler binario
        char arquivoBin[50];
        scanf("%s", arquivoBin);

        LISTA *lista = getRegistrosFromBin(arquivoBin);

        imprimirLista(lista);
    }
    else if (strcmp(operacao, "3") == 0)
    {
        // Buscar
        char arquivoBin[50];
        scanf("%s", arquivoBin);

        int numOperacoes;
        scanf("%d", &numOperacoes);

        LISTA *lista = getRegistrosFromBin(arquivoBin);

        for (int i = 0; i < numOperacoes; i++)
        {
            printf("BUSCA %d\n", i + 1);

            int m;
            scanf("%i", &m);
            REGISTRO **registros;

            for (int j = 0; j < m; j++)
            {
                char campo[50];
                scanf("%s", campo);

                if(strcmp(campo, "id") == 0)
                {
                    int id;
                    scanf("%i", &id);
                    if(j == 0)
                    {
                        registros = buscaPorId(lista, id);
                    }
                    else
                    {
                        registros = intersecaoDoisRegistros(registros, buscaPorId(lista, id));
                    }
                }
                else if(strcmp(campo, "nome") == 0)
                {
                    char nome[50];
                    scan_quote_string(nome);
                    if(j == 0)
                    {
                        registros = buscaPorNome(lista, nome);
                    }
                    else
                    {
                        registros = intersecaoDoisRegistros(registros, buscaPorNome(lista, nome));
                    }
                }
                else if(strcmp(campo, "idade") == 0)
                {
                    int idade;
                    scanf("%i", &idade);
                    if(j == 0)
                    {
                        registros = buscaPorIdade(lista, idade);
                    }
                    else
                    {
                        registros = intersecaoDoisRegistros(registros, buscaPorIdade(lista, idade));
                    }
                }
                else if(strcmp(campo, "nomeClube") == 0)
                {
                    char clube[50];
                    scan_quote_string(clube);
                    if(j == 0)
                    {
                        registros = buscaPorClube(lista, clube);
                    }
                    else
                    {
                        registros = intersecaoDoisRegistros(registros, buscaPorClube(lista, clube));
                    }
                }
                else if(strcmp(campo, "nacionalidade") == 0)
                {
                    char nacionalidade[50];
                    scan_quote_string(nacionalidade);
                    if(j == 0)
                    {
                        registros = buscaPorNacionalidade(lista, nacionalidade);
                    }
                    else
                    {
                        registros = intersecaoDoisRegistros(registros, buscaPorNacionalidade(lista, nacionalidade));
                    }
                }
                else
                {
                    printf("Campo invalido\n");
                }
            }
            imprimirRegistros(registros);
        }
    }
    else
    {
        printf("Operacao invalida\n");
    }

    // cabecalho = getCabecalhoFromBin("bin");
    // LISTA *lista2 = getRegistrosFromBin("bin");
    // BuscaNacionalidadeEIdade(lista, "FRANCE", 24);
    //teste();
    return 0;
}