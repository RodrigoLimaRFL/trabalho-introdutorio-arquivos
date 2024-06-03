#include "escreveBin.h"
#include "cabecalho.h"
#include "funcoes_fornecidas.h"
#include "interpreta-bin.h"

// Função que pega os registros do arquivo binário e imprime eles na tela
void imprimeRegistrosFromBin(char *filePath)
{
    int impressoes = 0;
    FILE *file = fopen(filePath, "rb"); // verifica se ocorreu um erro ao abrir o arquivo no modo leitura
    if (file == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return;
    }

    int i = 0;

    // cria um cabeçalho e chama a função lerCabecalhoFromBin para atribuir os valores a ele
    CABECALHO *cabecalho = getCabecalhoFromBin(file);

    if (getStatus(cabecalho) == '0')
    {
        printf("Falha no processamento do arquivo.");
        fclose(file); // fecha o arquivo
        return;
    }

    long long int byteOffset = getProxByteOffset(cabecalho);
    int numRegistros = getNroRegArq(cabecalho) + getNroRem(cabecalho); // número total de registros
    byteOffset = 25;

    if (numRegistros == 0) // verifica se o arquivo não possui registros
    {
        printf("Registro inexistente.\n\n");
        fclose(file); // fecha o arquivo
        return;
    }

    for (i = 0; i < numRegistros; i++)
    {
        REGISTRO *registro = lerRegistroFromBin(byteOffset, file); // lê um registro do arquivo binário
        byteOffset += get_tamanhoRegistro(registro); // muda o byteOffset para a posição do próximo registro
        impressoes += imprimeRegistro(registro);
    }

    if (impressoes == 0)
    {
        printf("Registro inexistente.\n\n");
    }

    apagarCabecalho(cabecalho); // libera a memória do cabeçalho

    fclose(file); // fecha o arquivo
    return;
}

int imprimeRegistro(REGISTRO *registro)
{
    if (get_removido(registro) == '0')
    { // se o registro não foi removido, imprime seus dados na tela

        // recebe o valor dos atributos do registro
        char *nomeClube = get_nomeClube(registro);
        char *nacionalidade = get_nacionalidade(registro);
        char *nomeJogador = get_nomeJogador(registro);

        printf("Nome do Jogador: ");
        if (strcmp(nomeJogador, "SEM DADO") == 0) // se o nome do jogador for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere do nome do jogador
        {
            for (int j = 0; j < get_tamNomeJogador(registro); j++)
            {
                printf("%c", nomeJogador[j]);
            }
            printf("\n");
        }

        printf("Nacionalidade do Jogador: ");
        if (strcmp(nacionalidade, "SEM DADO") == 0) // se a nacionalidade for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere da nacionalidade
        {
            for (int j = 0; j < get_tamNacionalidade(registro); j++)
            {
                printf("%c", nacionalidade[j]);
            }
            printf("\n");
        }

        printf("Clube do Jogador: ");
        if (strcmp(nomeClube, "SEM DADO") == 0) // se o nome do clube for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere do nome do clube
        {
            for (int j = 0; j < get_tamNomeClube(registro); j++)
            {
                printf("%c", nomeClube[j]);
            }
            printf("\n");
        }
        printf("\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

void imprimeRegistrosBuscados(char *arquivo)
{
    int numOperacoes;
    scanf("%d", &numOperacoes); // lê o número de buscas a serem feitas

    for (int i = 0; i < numOperacoes; i++)
    {
        int impressoes = 0;
        int m;
        scanf("%i", &m); // lê o número de parâmetros da busca

        FILE *file = fopen(arquivo, "rb"); // verifica se ocorreu um erro ao abrir o arquivo no modo leitura
        if (file == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return;
        }

        // cria um cabeçalho e chama a função lerCabecalhoFromBin para atribuir os valores a ele
        CABECALHO *cabecalho = getCabecalhoFromBin(file);

        if (getStatus(cabecalho) == '0')
        {
            printf("Falha no processamento do arquivo.");
            fclose(file); // fecha o arquivo
            return;
        }

        long long int byteOffset = getProxByteOffset(cabecalho);
        int numRegistros = getNroRegArq(cabecalho) + getNroRem(cabecalho); // número total de registros
        byteOffset = 25;

        if (numRegistros == 0) // verifica se o arquivo não possui registros
        {
            printf("Registro inexistente.\n\n");
            fclose(file); // fecha o arquivo
            return;
        }

        char campos[5][50];
        char parametros[5][50];
        int id, idade;
        char nome[50], nomeClube[50], nacionalidade[50];
        for (int j = 0; j < m; j++)
        {
            scanf("%s", campos[j]); // lê um parâmetro da busca
            if (strcmp(campos[j], "id") == 0)
            {
                scanf("%i", &id); // lê o id da busca
                snprintf(parametros[j], 50, "%i", id);
                printf("%s\n", parametros[j]);
            }
            else if (strcmp(campos[j], "nome") == 0)
            {
                scan_quote_string(nome);
                strcpy(parametros[j], nome);
            }
            else if (strcmp(campos[j], "idade") == 0)
            {
                scanf("%i", &idade);
                snprintf(parametros[j], 50, "%i", idade);
            }
            else if (strcmp(campos[j], "nomeClube") == 0)
            {
                scan_quote_string(nomeClube);
                strcpy(parametros[j], nomeClube);
            }
            else if (strcmp(campos[j], "nacionalidade") == 0)
            {
                scan_quote_string(nacionalidade);
                strcpy(parametros[j], nacionalidade);
            }
            else
            {
                printf("Campo invalido\n");
            }
        }

        printf("Busca %d\n", i + 1);
        printf("\n");

        for (int j = 0; j < numRegistros; j++)
        {
            REGISTRO *registro = lerRegistroFromBin(byteOffset, file); // lê um registro do arquivo binário
            byteOffset += get_tamanhoRegistro(registro); // muda o byteOffset para a posição do próximo registro

            int imprimir = 1;
            if (get_removido(registro) == '1')
            {
                imprimir = 0;
            }
            else
            {
                for (int k = 0; k < m; k++)
                {
                    if (strcmp(campos[k], "id") == 0)
                    { // verifica se o parâmetro da busca é o id
                        if (id != get_id(registro))
                        {
                            imprimir = 0;
                        }
                    }
                    else if (strcmp(campos[k], "nome") == 0)
                    {
                        if (strcmp(nome, get_nomeJogador(registro)) != 0)
                        {
                            imprimir = 0;
                        }
                    }
                    else if (strcmp(campos[k], "idade") == 0)
                    {
                        if (idade != get_idade(registro))
                        {
                            imprimir = 0;
                        }
                    }
                    else if (strcmp(campos[k], "nomeClube") == 0)
                    {
                        if (strcmp(nomeClube, get_nomeClube(registro)) != 0)
                        {
                            imprimir = 0;
                        }
                    }
                    else if (strcmp(campos[k], "nacionalidade") == 0)
                    {
                        if (strcmp(nacionalidade, get_nacionalidade(registro)) != 0)
                        {
                            imprimir = 0;
                        }
                    }
                }
            }
            if (imprimir == 1)
            {
                imprimeRegistro(registro);
                impressoes++;
            }
        }
        fclose(file);
        apagarCabecalho(cabecalho); // libera a memória do cabeçalho

        /*if(impressoes == 0) {
          printf("Registro inexistente.\n\n");
        }*/
    }
}

void removerRegistrosBuscados(char *arquivo, REMOVIDOS *listaRemovidos)
{
    int numOperacoes;
    scanf("%d", &numOperacoes); // lê o número de buscas a serem feitas

    for (int i = 0; i < numOperacoes; i++)
    {
        int removidos = 0;
        int m;
        scanf("%i", &m); // lê o número de parâmetros da busca

        FILE *file = fopen(arquivo, "wb+"); // verifica se ocorreu um erro ao abrir o arquivo no modo leitura e escrita
        if (file == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return;
        }

        // cria um cabeçalho e chama a função lerCabecalhoFromBin para atribuir os valores a ele
        CABECALHO *cabecalho = getCabecalhoFromBin(file);

        if (getStatus(cabecalho) == '0')
        {
            printf("Falha no processamento do arquivo.");
            fclose(file); // fecha o arquivo
            return;
        }

        long long int byteOffset = getProxByteOffset(cabecalho);
        int numRegistros = getNroRegArq(cabecalho) + getNroRem(cabecalho); // número total de registros
        byteOffset = 25;

        if (numRegistros == 0) // verifica se o arquivo não possui registros
        {
            printf("Registro inexistente.\n\n");
            fclose(file); // fecha o arquivo
            return;
        }

        char campos[5][50];
        char parametros[5][50];
        int id = -1, idade;
        char nome[50], nomeClube[50], nacionalidade[50];
        for (int j = 0; j < m; j++)
        {
            scanf("%s", campos[j]); // lê um parâmetro da busca
            if (strcmp(campos[j], "id") == 0)
            {
                scanf("%i", &id); // lê o id da busca
                                  // buscaId(id);
            }
            else if (strcmp(campos[j], "nome") == 0)
            {
                scan_quote_string(nome);
            }
            else if (strcmp(campos[j], "idade") == 0)
            {
                scanf("%i", &idade);
            }
            else if (strcmp(campos[j], "nomeClube") == 0)
            {
                scan_quote_string(nomeClube);
            }
            else if (strcmp(campos[j], "nacionalidade") == 0)
            {
                scan_quote_string(nacionalidade);
            }
            else
            {
                printf("Campo invalido\n");
            }
        }

        if (id != -1)
        {
            // removerRegistroId(file, id);
            fclose(file);
            apagarCabecalho(cabecalho);
            continue;
        }

        printf("Busca %d\n", i + 1);
        printf("\n");

        for (int j = 0; j < numRegistros; j++)
        {
            REGISTRO *registro = lerRegistroFromBin(byteOffset, file); // lê um registro do arquivo binário
            byteOffset += get_tamanhoRegistro(registro); // muda o byteOffset para a posição do próximo registro

            int remover = 1;
            if (get_removido(registro) == '1')
            {
                remover = 0; // indica se o registro deve ser removido
            }
            else
            {
                for (int k = 0; k < m; k++)
                {
                    if (strcmp(campos[k], "id") == 0)
                    { // verifica se o parâmetro da busca é o id
                        if (id != get_id(registro))
                        {
                            remover = 0;
                        }
                    }
                    else if (strcmp(campos[k], "nome") == 0)
                    {
                        if (strcmp(nome, get_nomeJogador(registro)) != 0)
                        {
                            remover = 0;
                        }
                    }
                    else if (strcmp(campos[k], "idade") == 0)
                    {
                        if (idade != get_idade(registro))
                        {
                            remover = 0;
                        }
                    }
                    else if (strcmp(campos[k], "nomeClube") == 0)
                    {
                        if (strcmp(nomeClube, get_nomeClube(registro)) != 0)
                        {
                            remover = 0;
                        }
                    }
                    else if (strcmp(campos[k], "nacionalidade") == 0)
                    {
                        if (strcmp(nacionalidade, get_nacionalidade(registro)) != 0)
                        {
                            remover = 0;
                        }
                    }
                }
            }
            if (remover == 1)
            {
                char status = '1';
                fwrite(&status, 1, 1, file);
                REGISTRO_INDICE *registroIndice = criarRegistroIndice();
                setIndexRegistroIndice(registroIndice, get_id(registro));
                setByteOffsetRegistroIndice(registroIndice, byteOffset);
                adicionarRegistroRemovido(listaRemovidos, registroIndice, get_tamanhoRegistro(registro));
                removidos++;
            }
        }
        fclose(file);
        apagarCabecalho(cabecalho); // libera a memória do cabeçalho

        if (removidos == 0)
        {
            // printf("Registro inexistente.\n\n");
        }
    }
}