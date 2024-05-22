#include <stdio.h>

#include "gerencia-arquivo.h"
#include "lista.h"
#include "interpreta-bin.h"
#include "cabecalho.h"
#include "funcoes_fornecidas.h"
#include "criarIndice.h"

int main() {
    char operacao[2];
    scanf("%s", operacao); // lê qual operação que vai realizar
    
    if(strcmp(operacao, "1") == 0)
    {
        // Ler Csv e escrever binario
        char arquivoCsv[50];
        scanf("%s", arquivoCsv); // lê o nome do arquivo csv
        char arquivoBin[50];
        scanf("%s", arquivoBin); // lê o nome do arquivo binário

        CABECALHO *cabecalho = criarCabecalho();
        setStatus(cabecalho, '1');
        setProxByteOffset(cabecalho, 0);

        LISTA *lista = lerCsv(arquivoCsv); // armazena os dados do arquivo csv na lista de registros
        setValoresCabecalho(cabecalho, lista); // define os valores dos campos do cabeçalho
        escreveBinario(cabecalho, lista, arquivoBin); // escreve os dados do cabeçalho e dos registros no arquivo binário

        binarioNaTela(arquivoBin);

        apagarCabecalho(cabecalho); // libera a memória do cabeçalho
        apagarLista(lista); // libera a memória da lista de registros
    }
    else if (strcmp(operacao, "2") == 0)
    {
        // Ler binario
        char arquivoBin[50];
        scanf("%s", arquivoBin);

        LISTA *lista = getRegistrosFromBin(arquivoBin); // armazena os registros do arquivo binário na lista
        
        if (lista)
            imprimirLista(lista); // imprime todos os registros da lista

        apagarLista(lista); // libera a memória da lista de registros
    }
    else if (strcmp(operacao, "3") == 0)
    {
        // Buscar
        char arquivoBin[50];
        scanf("%s", arquivoBin);

        int numOperacoes;
        scanf("%d", &numOperacoes); // lê o número de buscas a serem feitas

        LISTA *lista = getRegistrosFromBin(arquivoBin); // armazena os registros do arquivo binário na lista de registros 

        for (int i = 0; i < numOperacoes; i++)
        {
            printf("Busca %d\n", i + 1);
            printf("\n");

            int m;
            scanf("%i", &m); // lê o número de parâmetros da busca
            REGISTRO **registros;

            for (int j = 0; j < m; j++)
            {
                char campo[50];
                scanf("%s", campo); // lê um parâmetro da busca

                if(strcmp(campo, "id") == 0) // verifica se o parâmetro da busca é o id
                {
                    int id;
                    scanf("%i", &id); // lê o id da busca
                    if(j == 0) // se é o primeiro parâmetro da busca, faz a busca pelo id
                    {
                        registros = buscaPorId(lista, id);
                    }
                    else // se não, faz a intersecao das buscas realizadas anteriormente com a busca pelo id
                    {
                        registros = intersecaoDoisRegistros(registros, buscaPorId(lista, id));
                    }
                }
                else if(strcmp(campo, "nome") == 0) // verifica se o parâmetro da busca é o nome do jogador
                {
                    char nome[50];
                    scan_quote_string(nome); // lê o nome do jogador 
                    if(j == 0) // se é o primeiro parâmetro da busca, faz a busca pelo nome
                    {
                        registros = buscaPorNome(lista, nome);
                    }
                    else // se não, faz a intersecao das buscas realizadas anteriormente com a busca pelo nome
                    {
                        registros = intersecaoDoisRegistros(registros, buscaPorNome(lista, nome));
                    }
                }
                else if(strcmp(campo, "idade") == 0) // verifica se o parâmetro da busca é a idade do jogador
                {
                    int idade;
                    scanf("%i", &idade); // lê a idade do jogador
                    if(j == 0) // se é o primeiro parâmetro da busca, faz a busca pela idade
                    {
                        registros = buscaPorIdade(lista, idade);
                    }
                    else // se não, faz a intersecao das buscas realizadas anteriormente com a busca pela idade
                    {
                        registros = intersecaoDoisRegistros(registros, buscaPorIdade(lista, idade));
                    }
                }
                else if(strcmp(campo, "nomeClube") == 0) // verifica se o parâmetro da busca é o nome do clube
                {
                    char clube[50];
                    scan_quote_string(clube); // lê o nome do clube
                    if(j == 0) // se é o primeiro parâmetro da busca, faz a busca pelo clube
                    {
                        registros = buscaPorClube(lista, clube);
                    }
                    else // se não, faz a intersecao das buscas realizadas anteriormente com a busca pelo clube
                    {
                        registros = intersecaoDoisRegistros(registros, buscaPorClube(lista, clube));
                    }
                }
                else if(strcmp(campo, "nacionalidade") == 0) // verifica se o parâmetro da busca é a nacionalidade do jogador
                {
                    char nacionalidade[50];
                    scan_quote_string(nacionalidade); // lê a nacionalidade do jogador
                    if(j == 0) // se é o primeiro parâmetro da busca, faz a busca pela nacionalidade
                    {
                        registros = buscaPorNacionalidade(lista, nacionalidade);
                    }
                    else // se não, faz a intersecao das buscas realizadas anteriormente com a busca pela nacionalidade
                    {
                        registros = intersecaoDoisRegistros(registros, buscaPorNacionalidade(lista, nacionalidade));
                    }
                }
                else // se o campo de busca não estiver definido, imprime que o campo é inválido
                {
                    printf("Campo invalido\n");
                }
            }
            imprimirRegistros(registros); // imprime os registros que satisfazem as condições de busca
            free(registros); // libera a memória do vetor de registros
        }
        apagarLista(lista); // libera a memória da lista de registros
    }
    else if(strcmp(operacao, "4") == 0)
    {
        // adicionar nome do indice
        // Ler binario
        char arquivoBin[50];
        scanf("%s", arquivoBin);

        LISTA *lista = getRegistrosFromBin(arquivoBin); // armazena os registros do arquivo binário na lista
        CABECALHO *cabecalho = criarCabecalho();
        
        if (lista)
            criarArquivoDeIndice(lista,cabecalho);
    }
    else // se a operação for diferente de 1, 2 ou 3, imprime, imprime que a operação é inválida
    {
        printf("Operacao invalida\n");
    }

    return 0;
}