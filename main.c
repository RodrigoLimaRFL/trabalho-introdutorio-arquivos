#include <stdio.h>

#include "gerencia-arquivo.h"
#include "lista.h"
#include "interpreta-bin.h"
#include "cabecalho.h"

int main() {
    char operacao[2];
    scanf("%s", operacao);
    
    if(strcmp(operacao, "1") == 0)
    {
        // Ler Csv e escrever binario
        char arquivoCsv[50];
        scanf("%s", arquivoCsv);
        printf("arquivoCsv: %s\n", arquivoCsv);
        char arquivoBin[50];
        scanf("%s", arquivoBin);
        printf("arquivoBin: %s\n", arquivoBin);

        printf("arquivoCsv: %s\n", arquivoCsv);
        printf("arquivoBin: %s\n", arquivoBin);

        CABECALHO *cabecalho = criarCabecalho();
        LISTA *lista = lerCsv(arquivoCsv);
        escreveBinario(cabecalho, lista, arquivoBin);
    }
    else if (strcmp(operacao, "2") == 0)
    {
        // Ler binario
        char arquivoBin[50];
        scanf("%s", arquivoBin);
        printf("arquivoBin: %s\n", arquivoBin);

        LISTA *lista = getRegistrosFromBin(arquivoBin);
    }
    else if (strcmp(operacao, "3") == 0)
    {
        // Buscar
        char arquivoBin[50];
        scanf("%s", arquivoBin);
        printf("arquivoBin: %s\n", arquivoBin);

        int numOperacoes;
        scanf("%d", &numOperacoes);
        printf("numOperacoes: %d\n", numOperacoes);

        LISTA *lista = getRegistrosFromBin(arquivoBin);

        for (int i = 0; i < numOperacoes; i++)
        {
            int m;
            scanf("%i", &m);
            printf("m: %i\n", m);
            REGISTRO **registros;

            for (int j = 0; j < m; j++)
            {
                char campo[50];
                scanf("%s", campo);
                printf("campo: %s\n", campo);

                if(strcmp(campo, "id") == 0)
                {
                    int id;
                    scanf("%i", &id);
                    printf("id: %i\n", id);
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
                    scanf("%s", nome);
                    printf("nome: %s\n", nome);
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
                    printf("idade: %i\n", idade);
                    if(j == 0)
                    {
                        registros = buscaPorIdade(lista, idade);
                    }
                    else
                    {
                        registros = intersecaoDoisRegistros(registros, buscaPorIdade(lista, idade));
                    }
                }
                else if(strcmp(campo, "clube") == 0)
                {
                    char clube[50];
                    scanf("%s", clube);
                    printf("clube: %s\n", clube);
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
                    scanf("%s", nacionalidade);
                    printf("nacionalidade: %s\n", nacionalidade);
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