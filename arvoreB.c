#include "arvoreB.h"


// aumenta a altura dos nos. 0 == folha
int aumentarAlturaRecursivamente(FILE *arquivo, int rrnRaiz)
{
    REGISTRO_ARVORE_B *registro = lerRegistroArvoreB(arquivo, rrnRaiz);

    int nroDescendentes = 0;

    for(int i = 0; i < ORDEM_ARVORE_B; i++)
    {
        if(getDescendente(registro, i) != -1)
        {
            nroDescendentes++;
        }
    }

    int maxAltura = -1;
    int minAltura = -1;

    if(nroDescendentes == 0) // eh folha
    {
        setAlturaNoRegistroArvoreB(registro, 0);
        escreverRegistroArvoreB(registro, arquivo, rrnRaiz);
        apagarRegistroArvoreB(registro);
        return 0;
    }

    for(int i = 0; i < nroDescendentes; i++)
    {
        int rrnDescendente = getDescendente(registro, i);
        int altura = aumentarAlturaRecursivamente(arquivo, rrnDescendente);
        /*if(minAltura == -1 || altura < minAltura)
        {
            minAltura = altura;
        }*/
        if(altura > maxAltura)
        {
            maxAltura = altura;
        }
    }

    setAlturaNoRegistroArvoreB(registro, maxAltura + 1);
    //setAlturaNoRegistroArvoreB(registro, minAltura + 1);
    escreverRegistroArvoreB(registro, arquivo, rrnRaiz);
    apagarRegistroArvoreB(registro);

    return maxAltura + 1;
}

// divide o no e retorna a nova raiz
bool splitNo(FILE *arquivo, CABECALHO_ARVORE_B *cabecalho, int chavePromovida, int byteOffsetPromovido, REGISTRO_ARVORE_B **caminho, REGISTRO_ARVORE_B *filhoEsq, REGISTRO_ARVORE_B *filhoDir, int nivel)
{ 
    int chaves[ORDEM_ARVORE_B]; //numero de chaves em um registro + 1
    int byteOffsets[ORDEM_ARVORE_B]; //numero de chaves em um registro + 1

    /*printf("chavePromovida: %d\n", chavePromovida);
    printf("byteOffsetPromovido: %d\n", byteOffsetPromovido);

    printf("chave filho esq: %d\n", getChave(filhoEsq, 0));
    printf("chave filho dir: %d\n", getChave(filhoDir, 0));*/

    // variaveis para detectar onde colocar a nova chave
    int index = 0;
    bool inserido = false;
    int posicao = -1;
    for(int i = 0; i < ORDEM_ARVORE_B; i++)
    {
        int chaveLida = getChave(caminho[nivel], index);
        //printf("Chave lida: %d\n", chaveLida);
        if(chavePromovida == chaveLida) // se a chave ja existe
        {
            return false;
        }
        if(!inserido && chavePromovida < chaveLida) // colocando nova chave
        {
            inserido = true;
            chaves[i] = chavePromovida;
            byteOffsets[i] = byteOffsetPromovido;
            posicao = i;
            continue;
        }
        if(chaveLida == -1 && i == ORDEM_ARVORE_B - 1) // nao achou chave menor, insere no fim
        {
            inserido = true;
            chaves[i] = chavePromovida;
            byteOffsets[i] = byteOffsetPromovido;
            posicao = i;
            break;
        }
        chaves[i] = chaveLida;
        byteOffsets[i] = getByteOffsetRegistroArvoreB(caminho[nivel], index);
        index++;
    }

    /*for(int i = 0; i< ORDEM_ARVORE_B; i++)
    {
        printf("Chave %d: %d\n", i, chaves[i]);
    }*/

    // chave a ser promovida
    chavePromovida = chaves[ORDEM_ARVORE_B / 2 - 1];
    byteOffsetPromovido = byteOffsets[ORDEM_ARVORE_B / 2 - 1];

    // detecta se o no eh folha
    bool isFolha = false;
    if(getAlturaNoRegistroArvoreB(caminho[nivel]) == 0)
    {
        isFolha = true;
    }

    // registros a serem criados
    REGISTRO_ARVORE_B *registroEsquerdo = criarRegistroArvoreBVazio();
    int maiorChaveEsquerda = -1;
    REGISTRO_ARVORE_B *registroDireito = criarRegistroArvoreBVazio();
    int menorChaveDireita = -1;

    if(isFolha) // se for folha, apenas inserimos as chaves nos novos registros
    {
        for(int i = 0; i < ORDEM_ARVORE_B / 2 - 1; i++) // insere as chaves no registro esquerdo exceto a ultima
        {
            inserirChaveRegistroArvoreB(registroEsquerdo, chaves[i], byteOffsets[i]);
        }
        for(int i = ORDEM_ARVORE_B / 2; i < ORDEM_ARVORE_B; i++) // insere as chaves no registro direito
        {
            inserirChaveRegistroArvoreB(registroDireito, chaves[i], byteOffsets[i]);
        }
    }
    else // caso contrario, inserimos as chaves e os descendentes
    {
        int rrnFilhoEsq = getRRNRegistroArvoreB(filhoEsq);
        int rrnFilhoDir = getRRNRegistroArvoreB(filhoDir);

        long long int descendentes[ORDEM_ARVORE_B + 1];

        index = 0;
        for(int i = 0; i < ORDEM_ARVORE_B; i++) // pega cada descendente em ordem crescente
        {
            if(i == posicao)
            {
                descendentes[i] = rrnFilhoEsq;
                descendentes[i + 1] = rrnFilhoDir;
                index += 2;
                continue;
            }
            descendentes[index] = getDescendente(caminho[nivel], i);
            index++;
        }

        apagarRegistroArvoreB(filhoEsq);
        apagarRegistroArvoreB(filhoDir);

        /*for(int i = 0; i < ORDEM_ARVORE_B + 1; i++)
        {
            printf("Descendente %d: %lld\n", i, descendentes[i]);
        }*/
        int chavesDescendentes[ORDEM_ARVORE_B + 1];

        for(int i = 0; i < ORDEM_ARVORE_B + 1; i++) // pega as chaves dos descendentes
        {
            REGISTRO_ARVORE_B *registroDescendente = lerRegistroArvoreB(arquivo, descendentes[i]);
            chavesDescendentes[i] = getChave(registroDescendente, 0);
            apagarRegistroArvoreB(registroDescendente);
        }

        /*for(int i = 0; i < ORDEM_ARVORE_B + 1; i++)
        {
            printf("Chave Descendente %d: %d\n", i, chavesDescendentes[i]);
        }*/

        for(int i = 0; i < ORDEM_ARVORE_B / 2 - 1; i++) // insere as chaves no registro esquerdo exceto a ultima
        {
            inserirChaveRegistroArvoreB(registroEsquerdo, chaves[i], byteOffsets[i]);
        }

        for(int i = 0; i <= ORDEM_ARVORE_B / 2 - 1; i++) // insere os descendentes no registro esquerdo
        {
            inserirDescendenteRegistroArvoreB(registroEsquerdo, descendentes[i], chavesDescendentes[i]);
        }
        
        for(int i = ORDEM_ARVORE_B / 2; i < ORDEM_ARVORE_B; i++) // insere as chaves no registro direito
        {
            inserirChaveRegistroArvoreB(registroDireito, chaves[i], byteOffsets[i]);
        }

        for(int i = ORDEM_ARVORE_B / 2; i <= ORDEM_ARVORE_B; i++) // insere os descendentes no registro direito
        {
            inserirDescendenteRegistroArvoreB(registroDireito, descendentes[i], chavesDescendentes[i]);
        }

        //printf("inseriu chaves e descendentes\n");
    }

    // escreve os registros particionados
    int rrnAtual = getRRNRegistroArvoreB(caminho[nivel]);
    int proxRRN = getProxRRNCabecalhoArvoreB(cabecalho);

    setRRNRegistroArvoreB(registroEsquerdo, rrnAtual);
    setRRNRegistroArvoreB(registroDireito, proxRRN);
    escreverRegistroArvoreB(registroEsquerdo, arquivo, rrnAtual);
    escreverRegistroArvoreB(registroDireito, arquivo, proxRRN);

    maiorChaveEsquerda = getChave(registroEsquerdo, ORDEM_ARVORE_B / 2 - 1);
    menorChaveDireita = getChave(registroDireito, 0);

    //printf("escreveu registros particionados\n");

    // se o pai nao tiver espaço para promocao, divida-o
    if(nivel > 0 && getNroChavesRegistroArvoreB(caminho[nivel - 1]) == ORDEM_ARVORE_B - 1) // se o pai existe e está cheio
    {
        // atualiza o registro do pai no caminho
        /*printf("Pai cheio, dividindo...\n");
        printf("registro esquerdo\n");
        imprimirRegistroArvoreB(registroEsquerdo);
        printf("registro direito\n");
        imprimirRegistroArvoreB(registroDireito);*/
        setProxRRNCabecalhoArvoreB(cabecalho, proxRRN + 1); // talvez de erro se o registro ja existe
        if(!splitNo(arquivo, cabecalho, chavePromovida, byteOffsetPromovido, caminho, registroEsquerdo, registroDireito, nivel - 1))
        {
            apagarRegistroArvoreB(registroEsquerdo);
            apagarRegistroArvoreB(registroDireito);
            return false;
        }
    }
    else // caso contrario, insira a chave promovida no pai
    {
        // escreve os registros particionados
        escreverRegistroArvoreB(registroEsquerdo, arquivo, rrnAtual);
        escreverRegistroArvoreB(registroDireito, arquivo, proxRRN);

        maiorChaveEsquerda = getChave(registroEsquerdo, ORDEM_ARVORE_B / 2 - 2);
        menorChaveDireita = getChave(registroDireito, 0);

        if(nivel == 0) // caso raiz
        {
            //printf("raiz\n");
            REGISTRO_ARVORE_B *novaRaiz = criarRegistroArvoreBVazio();

            int rrnRaiz = proxRRN + 1;

            //printf("RRN Raiz: %d\n", rrnRaiz);

            /*printf("registro esquerdo\n");
            imprimirRegistroArvoreB(registroEsquerdo);

            printf("registro direito\n");
            imprimirRegistroArvoreB(registroDireito);*/

            // escreve a nova raiz
            inserirChaveRegistroArvoreB(novaRaiz, chavePromovida, byteOffsetPromovido);
            inserirDescendenteRegistroArvoreB(novaRaiz, rrnAtual, maiorChaveEsquerda);
            inserirDescendenteRegistroArvoreB(novaRaiz, proxRRN, menorChaveDireita);
            setRRNRegistroArvoreB(novaRaiz, rrnRaiz);
            escreverRegistroArvoreB(novaRaiz, arquivo, rrnRaiz);

            /*printf("escreveu nova raiz\n");
            imprimirRegistroArvoreB(novaRaiz);

            printf("todos os registros:\n");*/

            /*for(int i = 0; i <= 6; i++)
            {
                REGISTRO_ARVORE_B *registro = lerRegistroArvoreB(arquivo, i);
                setRRNRegistroArvoreB(registro, i);
                imprimirRegistroArvoreB(registro);
                apagarRegistroArvoreB(registro);
                printf("\n");
            }*/

            // reescreve o cabecalho
            CABECALHO_ARVORE_B *cabecalho = lerCabecalhoArvoreB(arquivo);
            setNoRaizCabecalhoArvoreB(cabecalho, rrnRaiz);
            setProxRRNCabecalhoArvoreB(cabecalho, rrnRaiz + 1);
            setNroChavesCabecalhoArvoreB(cabecalho, getNroChavesCabecalhoArvoreB(cabecalho) + 1);
            escreverCabecalhoArvoreB(arquivo, cabecalho);

            //printf("antes de aumentar altura\n");

            //imprimirArvoreBGraphviz(arquivo);

            // aumenta a altura dos nos
            aumentarAlturaRecursivamente(arquivo, rrnRaiz);

            /*printf("depois de aumentar altura\n");

            printf("RRN Raiz: %d\n", rrnRaiz);
            printf("Nova Raiz: \n");
            imprimirRegistroArvoreB(novaRaiz);
            printf("\n");
            printf("RRN Esquerdo: %d\n", rrnAtual);
            printf("Registro Esquerdo: \n");
            imprimirRegistroArvoreB(registroEsquerdo);
            printf("\n");
            printf("RRN Direito: %d\n", proxRRN);
            printf("Registro Direito: \n");
            imprimirRegistroArvoreB(registroDireito);
            printf("\n\n");*/

            apagarRegistroArvoreB(registroEsquerdo);
            apagarRegistroArvoreB(registroDireito);
            apagarRegistroArvoreB(novaRaiz);
            apagarCabecalhoArvoreB(cabecalho);
        }
        else // caso nao seja raiz
        {
            REGISTRO_ARVORE_B *registroPai = lerRegistroArvoreB(arquivo, getRRNRegistroArvoreB(caminho[nivel - 1]));

            // escreve os registros particionados
            escreverRegistroArvoreB(registroEsquerdo, arquivo, rrnAtual);
            escreverRegistroArvoreB(registroDireito, arquivo, proxRRN);

            // escreve o pai
            inserirChaveRegistroArvoreB(registroPai, chavePromovida, byteOffsetPromovido);
            //inserirDescendenteRegistroArvoreB(registroPai, rrnAtual, maiorChaveEsq);
            inserirDescendenteRegistroArvoreB(registroPai, proxRRN, menorChaveDireita);
            escreverRegistroArvoreB(registroPai, arquivo, getRRNRegistroArvoreB(caminho[nivel - 1]));

            // reescreve o cabecalho
            setProxRRNCabecalhoArvoreB(cabecalho, proxRRN + 1);
            setNroChavesCabecalhoArvoreB(cabecalho, getNroChavesCabecalhoArvoreB(cabecalho) + 1);
            escreverCabecalhoArvoreB(arquivo, cabecalho);

            // aumenta a altura dos nos
            aumentarAlturaRecursivamente(arquivo, getRRNRegistroArvoreB(caminho[nivel - 1]));

            /*printf("RRN Pai: %d\n", getRRNRegistroArvoreB(caminho[nivel - 1]));
            printf("Registro Pai: \n");
            imprimirRegistroArvoreB(registroPai);
            printf("\n");
            printf("RRN Esquerdo: %d\n", rrnAtual);
            printf("Registro Esquerdo: \n");
            imprimirRegistroArvoreB(registroEsquerdo);
            printf("\n");
            printf("RRN Direito: %d\n", proxRRN);
            printf("Registro Direito: \n");
            imprimirRegistroArvoreB(registroDireito);
            printf("\n\n");*/


            apagarRegistroArvoreB(registroEsquerdo);
            apagarRegistroArvoreB(registroDireito);
            apagarRegistroArvoreB(registroPai);
        }
    }

    return true;
}

void insercaoNaoCheio(FILE *arquivo, CABECALHO_ARVORE_B *cabecalho, int chave, int byteOffset, int rrnAtual, REGISTRO_ARVORE_B *registro)
{
    if(!inserirChaveRegistroArvoreB(registro, chave, byteOffset)) // se a chave ja existe
    {
        return;
    }
    setRRNRegistroArvoreB(registro, rrnAtual);

    /*printf("Inserindo %d em %d\n", chave, rrnAtual);
    imprimirRegistroArvoreB(registro);
    printf("\n");*/

    // escreve o registro no arquivo
    escreverRegistroArvoreB(registro, arquivo, rrnAtual);

    // atualiza o cabecalho
    setNroChavesCabecalhoArvoreB(cabecalho, getNroChavesCabecalhoArvoreB(cabecalho) + 1);
    escreverCabecalhoArvoreB(arquivo, cabecalho);
}

void insercaoArvoreBRecursiva(FILE *arquivo, CABECALHO_ARVORE_B *cabecalho, int chave, int byteOffset, int rrnAtual, REGISTRO_ARVORE_B **caminho, int nivel, int *tamCaminho)
{
    // le o registro atual
    REGISTRO_ARVORE_B *registro = lerRegistroArvoreB(arquivo, rrnAtual);

    // insere o registro no caminho percorrido
    setRRNRegistroArvoreB(registro, rrnAtual);
    caminho = realloc(caminho, sizeof(REGISTRO_ARVORE_B *) * (nivel + 1));
    caminho[nivel] = registro;
    *tamCaminho = nivel + 1;

    if(getAlturaNoRegistroArvoreB(registro) != 0) // no nao folha
    {
        /*printf("No nao folha, recursao...\n");
        imprimirRegistroArvoreB(registro);
        printf("\n");*/
        int chaves[ORDEM_ARVORE_B - 1];

        // pega as chaves do registro para realizar a busca
        for(int i = 0; i < getNroChavesRegistroArvoreB(registro); i++)
        {
            chaves[i] = getChave(registro, i);
        }

        // busca qual descendente deve ser seguido
        int posicao = 0;
        for(int i = 0; i < getNroChavesRegistroArvoreB(registro); i++)
        {
            if(chaves[i] == chave) // se a chave ja existe
            {
                for(int i = 0; i< *tamCaminho; i++)
                {
                    apagarRegistroArvoreB(caminho[i]);
                }
                free(caminho);
                return;
            }

            if(chaves[i] > chave)
            {
                posicao = i;
                break;
            }

            posicao++;
        }

        // segue o descendente
        int rrnDescendente = getDescendente(registro, posicao);
        return insercaoArvoreBRecursiva(arquivo, cabecalho, chave, byteOffset, rrnDescendente, caminho, nivel + 1, tamCaminho);
    }

    // no folha
    if(getNroChavesRegistroArvoreB(registro) < ORDEM_ARVORE_B - 1) // se o no nao estiver cheio
    {
        insercaoNaoCheio(arquivo, cabecalho, chave, byteOffset, rrnAtual, registro);
    }
    else // se o no estiver cheio
    {
        // divide o no
        //printf("No cheio, dividindo...\n");
        splitNo(arquivo, cabecalho, chave, byteOffset, caminho, NULL, NULL, nivel);
    }

    for(int i = 0; i< *tamCaminho; i++)
    {
        apagarRegistroArvoreB(caminho[i]);
    }
    free(caminho);
}

void imprimirArvoreBGraphvizRecursiva(FILE *arquivo, int rrnAtual)
{
    REGISTRO_ARVORE_B *registro = lerRegistroArvoreB(arquivo, rrnAtual);

    int nroChaves = getNroChavesRegistroArvoreB(registro);

    printf("node%d [label=\"", rrnAtual);

    for(int i = 0; i < nroChaves; i++)
    {
        printf("<f%d> %d | ", i, getChave(registro, i));
    }

    printf("\"];\n");

    for(int i = 0; i < ORDEM_ARVORE_B; i++)
    {
        if(getDescendente(registro, i) != -1)
        {
            int descendente = getDescendente(registro, i);
            printf("node%d:f%d -> node%d;\n", rrnAtual, i, descendente);
            imprimirArvoreBGraphvizRecursiva(arquivo, descendente);
        }
    }

    apagarRegistroArvoreB(registro);
}

void imprimirArvoreBGraphviz(FILE *arquivo)
{
    CABECALHO_ARVORE_B *cabecalho = lerCabecalhoArvoreB(arquivo);

    int rrnAtual = getNoRaizCabecalhoArvoreB(cabecalho);

    printf("digraph G {\n");

    imprimirArvoreBGraphvizRecursiva(arquivo, rrnAtual);

    printf("}\n");

    apagarCabecalhoArvoreB(cabecalho);

}

void inserirArvoreB(FILE *arquivo, int chave, long long int byteOffset)
{
    CABECALHO_ARVORE_B *cabecalho = lerCabecalhoArvoreB(arquivo);

    /*printf("Inserindo %d: \n", chave);
    printf("Cabecalho: \n");
    imprimirCabecalhoArvoreB(cabecalho);*/

    int nroChaves = getNroChavesCabecalhoArvoreB(cabecalho);

    if(nroChaves == 0) // arvore vazia
    {
        REGISTRO_ARVORE_B *registro = criarRegistroArvoreBVazio();
        // atualiza valores do registro
        setAlturaNoRegistroArvoreB(registro, 0);
        inserirChaveRegistroArvoreB(registro, chave, byteOffset);
        setRRNRegistroArvoreB(registro, 0);

        /*printf("Arvore vazia, inserido na raiz\n");
        imprimirRegistroArvoreB(registro);
        printf("\n");*/

        // escreve o registro no arquivo
        escreverRegistroArvoreB(registro, arquivo, 0);
        apagarRegistroArvoreB(registro);

        // atualiza cabecalho
        setNoRaizCabecalhoArvoreB(cabecalho, 0);
        setProxRRNCabecalhoArvoreB(cabecalho, 1);
        setNroChavesCabecalhoArvoreB(cabecalho, 1);

        escreverCabecalhoArvoreB(arquivo, cabecalho);
        apagarCabecalhoArvoreB(cabecalho);

        return;
    }

    REGISTRO_ARVORE_B **caminho = (REGISTRO_ARVORE_B **) malloc(sizeof(REGISTRO_ARVORE_B *) * 1);
    long long int rrnAtual = getNoRaizCabecalhoArvoreB(cabecalho);
    long long int proxRrn = getProxRRNCabecalhoArvoreB(cabecalho);
    int tamCaminho = 0; // variavel para guardar o tamanho do caminho (necessario para liberar memoria)

    //insercaoArvoreBRecursiva(arquivo, rrnAtual, chave, 0, proxRrn, caminho, byteOffset, cabecalho);
    insercaoArvoreBRecursiva(arquivo, cabecalho, chave, byteOffset, rrnAtual, caminho, 0, &tamCaminho);

    apagarCabecalhoArvoreB(cabecalho);
    //free(caminho);
}