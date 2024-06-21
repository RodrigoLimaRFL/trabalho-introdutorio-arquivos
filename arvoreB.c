#include "arvoreB.h"


bool particionarNo(FILE *arquivo, REGISTRO_ARVORE_B *registro, int rrnAtual, int chave, int altura, int proxRrn, int *caminho, long long int byteOffset, CABECALHO_ARVORE_B *cabecalho)
{
    if(altura != 0) // nao eh o no raiz
    {
        // pega o registro pai
        REGISTRO_ARVORE_B *registroPai = lerRegistroArvoreB(arquivo, caminho[altura - 1]);

        int nroChavesPai = getNroChavesRegistroArvoreB(registroPai);

        if(nroChavesPai == ORDEM_ARVORE_B - 1) // pai cheio
        {
            particionarNo(arquivo, registroPai, caminho[altura - 1], chave, altura - 1, proxRrn, caminho, byteOffset, cabecalho);
        }

        int chaves[ORDEM_ARVORE_B]; // pega todas as chaves do registro + a chave a inserir
        long long int byteOffsets[ORDEM_ARVORE_B];

        for (int i = 0; i < ORDEM_ARVORE_B; i++)
        {
            int chaveLida = getChave(registro, i);
            if(chave < chaveLida)
            {
                chaves[i] = chave;
                byteOffsets[i] = byteOffset;
                continue;
            }
            chaves[i] = chaveLida;
            byteOffsets[i] = getByteOffsetRegistroArvoreB(registro, i);
        }

        bool isFolha = false;

        int primeiroDescendente = getDescendente(registro, 0);

        if(primeiroDescendente == -1) // se nao ha o primeiro descendente, obrigatoriamente eh folha
        {
            isFolha = true;
        }

        REGISTRO_ARVORE_B *registroEsq = criarRegistroArvoreBVazio();
        REGISTRO_ARVORE_B *registroDir = criarRegistroArvoreBVazio();

        if(isFolha) // colocamos apenas as chaves nos novos registros
        {
            for(int i = 0; i < ORDEM_ARVORE_B / 2; i++) // insere as chaves no registro esquerdo
            {
                inserirChaveRegistroArvoreB(registroEsq, chaves[i], byteOffsets[i]);
            }
            for(int i = ORDEM_ARVORE_B / 2 + 1; i < ORDEM_ARVORE_B; i++) // insere as chaves exceto a primeira no registro direito
            {
                inserirChaveRegistroArvoreB(registroDir, chaves[i], byteOffsets[i]);
            }
        }
        else // colocamos as chaves e os descendentes nos novos registros
        {
            for(int i = 0; i < ORDEM_ARVORE_B / 2; i++) // insere as chaves no registro esquerdo
            {
                REGISTRO_ARVORE_B *registroDescendente = lerRegistroArvoreB(arquivo, getDescendente(registro, i));
                int chaveDescendente = getChave(registroDescendente, 0);
                inserirChaveRegistroArvoreB(registroEsq, chaves[i], byteOffsets[i]);
                inserirDescendenteRegistroArvoreB(registroEsq, getDescendente(registro, i), chaveDescendente);
                apagarRegistroArvoreB(registroDescendente);
            }
            for(int i = ORDEM_ARVORE_B / 2 + 1; i < ORDEM_ARVORE_B; i++) // insere as chaves exceto a primeira no registro direito
            {
                REGISTRO_ARVORE_B *registroDescendente = lerRegistroArvoreB(arquivo, getDescendente(registro, i));
                int chaveDescendente = getChave(registroDescendente, 0);
                inserirChaveRegistroArvoreB(registroEsq, chaves[i], byteOffsets[i]);
                inserirDescendenteRegistroArvoreB(registroEsq, getDescendente(registro, i), chaveDescendente);
                apagarRegistroArvoreB(registroDescendente);
            }
        }

        // escreve os registros particionados
        escreverRegistroArvoreB(registroEsq, arquivo, rrnAtual);
        escreverRegistroArvoreB(registroDir, arquivo, proxRrn);

        // chave a ser promovida
        int chaveMeio = chaves[ORDEM_ARVORE_B / 2];
        int byteOffsetMeio = byteOffsets[ORDEM_ARVORE_B / 2];

        // escreve o pai
        inserirChaveRegistroArvoreB(registroPai, chaveMeio, byteOffsetMeio);
        inserirDescendenteRegistroArvoreB(registroPai, proxRrn, chaveMeio);
        escreverRegistroArvoreB(registroPai, arquivo, caminho[altura - 1]);

        // reescreve o cabecalho
        setProxRRNCabecalhoArvoreB(cabecalho, proxRrn + 1);
        escreverCabecalhoArvoreB(arquivo, cabecalho);

        printf("Particionamento\n");
        printf("Registro Pai: ");
        imprimirRegistroArvoreB(registroPai);
        printf("\n");
        printf("Registro Esquerdo: ");
        imprimirRegistroArvoreB(registroEsq);
        printf("\n");
        printf("Registro Direito: ");
        imprimirRegistroArvoreB(registroDir);
        printf("\n\n");

        apagarRegistroArvoreB(registroEsq);
        apagarRegistroArvoreB(registroDir);
        apagarRegistroArvoreB(registroPai);
    }
    else // raiz
    {
        REGISTRO_ARVORE_B *novaRaiz = criarRegistroArvoreBVazio();
        int chaves[ORDEM_ARVORE_B]; // pega todas as chaves do registro + a chave a inserir
        int byteOffsets[ORDEM_ARVORE_B];

        for (int i = 0; i < ORDEM_ARVORE_B; i++)
        {
            int chaveLida = getChave(registro, i);
            if(chave < chaveLida)
            {
                chaves[i] = chave;
                byteOffsets[i] = byteOffset;
                continue;
            }
            chaves[i] = chaveLida;
            byteOffsets[i] = getByteOffsetRegistroArvoreB(registro, i);
        }

        REGISTRO_ARVORE_B *registroEsq = criarRegistroArvoreBVazio();
        REGISTRO_ARVORE_B *registroDir = criarRegistroArvoreBVazio();

        for(int i = 0; i < ORDEM_ARVORE_B / 2; i++) // insere as chaves no registro esquerdo
        {
            REGISTRO_ARVORE_B *registroDescendente = lerRegistroArvoreB(arquivo, getDescendente(registro, i));
            int chaveDescendente = getChave(registroDescendente, 0);
            inserirChaveRegistroArvoreB(registroEsq, chaves[i], byteOffsets[i]);
            inserirDescendenteRegistroArvoreB(registroEsq, getDescendente(registro, i), chaveDescendente);
            apagarRegistroArvoreB(registroDescendente);
        }
        for(int i = ORDEM_ARVORE_B / 2 + 1; i < ORDEM_ARVORE_B; i++) // insere as chaves exceto a primeira no registro direito
        {
            REGISTRO_ARVORE_B *registroDescendente = lerRegistroArvoreB(arquivo, getDescendente(registro, i));
            int chaveDescendente = getChave(registroDescendente, 0);
            inserirChaveRegistroArvoreB(registroEsq, chaves[i], byteOffsets[i]);
            inserirDescendenteRegistroArvoreB(registroEsq, getDescendente(registro, i), chaveDescendente);
            apagarRegistroArvoreB(registroDescendente);

            // escreve os registros particionados
            escreverRegistroArvoreB(registroEsq, arquivo, rrnAtual);
            escreverRegistroArvoreB(registroDir, arquivo, proxRrn);

            // chave a ser promovida
            int chaveMeio = chaves[ORDEM_ARVORE_B / 2];
            int byteOffsetMeio = byteOffsets[ORDEM_ARVORE_B / 2];
            int rrnRaiz = proxRrn + 1;

            // escreve a nova raiz
            inserirChaveRegistroArvoreB(novaRaiz, chaveMeio, byteOffsetMeio);
            inserirDescendenteRegistroArvoreB(novaRaiz, proxRrn, chaveMeio);
            escreverRegistroArvoreB(novaRaiz, arquivo, rrnRaiz);

            // reescreve o cabecalho
            CABECALHO_ARVORE_B *cabecalho = lerCabecalhoArvoreB(arquivo);
            setNoRaizCabecalhoArvoreB(cabecalho, rrnRaiz);
            setProxRRNCabecalhoArvoreB(cabecalho, rrnRaiz + 1);
            escreverCabecalhoArvoreB(arquivo, cabecalho);

            apagarRegistroArvoreB(registroEsq);
            apagarRegistroArvoreB(registroDir);
            apagarRegistroArvoreB(novaRaiz);
            apagarCabecalhoArvoreB(cabecalho);

            printf("Particionamento\n");
            printf("Nova Raiz: ");
            imprimirRegistroArvoreB(novaRaiz);
            printf("\n");
            printf("Registro Esquerdo: ");
            imprimirRegistroArvoreB(registroEsq);
            printf("\n");
            printf("Registro Direito: ");
            imprimirRegistroArvoreB(registroDir);
            printf("\n\n");
        }
    }
}

// insere em uma Arvore B recursivamente
bool insercaoArvoreBRecursiva(FILE *arquivo, int rrnAtual, int chave, int altura, int proxRrn, int *caminho, long long int byteOffset, CABECALHO_ARVORE_B *cabecalho)
{
    REGISTRO_ARVORE_B *registro = lerRegistroArvoreB(arquivo, rrnAtual);

    int nroChaves = getNroChavesRegistroArvoreB(registro);

    int nroDescendentes = 0;

    if(altura == 0 && nroChaves == 0) // arvore vazia
    {
        apagarRegistroArvoreB(registro);
        REGISTRO_ARVORE_B *registro = criarRegistroArvoreBVazio();
        setAlturaNoRegistroArvoreB(registro, 0);
        inserirChaveRegistroArvoreB(registro, chave, byteOffset);
        rrnAtual = 1;
        proxRrn = 2;
        escreverRegistroArvoreB(registro, arquivo, rrnAtual);
        setNroChavesCabecalhoArvoreB(cabecalho, 1);
        setProxRRNCabecalhoArvoreB(cabecalho, proxRrn);
        setNoRaizCabecalhoArvoreB(cabecalho, rrnAtual);
        escreverCabecalhoArvoreB(arquivo, cabecalho);
        
        printf("Arvore vazia\n");
        imprimirRegistroArvoreB(registro);
        printf("\n");

        apagarRegistroArvoreB(registro);
        return true;
    }

    caminho = realloc(caminho, sizeof(int) * (altura + 1));
    caminho[altura] = rrnAtual;

    if(nroDescendentes == 0 && nroChaves < ORDEM_ARVORE_B - 1) // no folha com espaço sobrando
    {
        inserirChaveRegistroArvoreB(registro, chave, byteOffset);
        escreverRegistroArvoreB(registro, arquivo, rrnAtual);

        printf("No folha com espaco\n");
        imprimirRegistroArvoreB(registro);
        printf("\n");

        setNroChavesCabecalhoArvoreB(cabecalho, getNroChavesCabecalhoArvoreB(cabecalho) + 1);
        apagarRegistroArvoreB(registro);

        return true;
    }

    if(nroDescendentes == 0 && nroChaves == ORDEM_ARVORE_B - 1) // no folha cheio
    {
        printf("No folha sem espaco\n");
        particionarNo(arquivo, registro, rrnAtual, chave, altura, proxRrn, caminho, byteOffset, cabecalho);
        setNroChavesCabecalhoArvoreB(cabecalho, getNroChavesCabecalhoArvoreB(cabecalho) + 1);
        apagarRegistroArvoreB(registro);
        printf("\n");

        return true;
    }

    if(nroDescendentes != 1){ // caso geral
        int posicao = 0;
        for(int i = 0; i < nroChaves; i++)
        {
            if(chave == getChave(registro, i)) // chave ja existe
            {
                return false;
            }
            if(chave < getChave(registro, i)) // busca a posicao da chave
            {
                posicao = i;
                break;
            }
        }

        int rrnDescendente = getDescendente(registro, posicao);
        insercaoArvoreBRecursiva(arquivo, rrnDescendente, chave, altura + 1, proxRrn, caminho, byteOffset, cabecalho);
    } 

    return true;
}


void inserirArvoreB(FILE *arquivo, int chave, long long int byteOffset)
{
    CABECALHO_ARVORE_B *cabecalho = lerCabecalhoArvoreB(arquivo);

    imprimirCabecalhoArvoreB(cabecalho);

    int *caminho = malloc(sizeof(int));
    long long int rrnAtual = getNoRaizCabecalhoArvoreB(cabecalho);
    long long int proxRrn = getProxRRNCabecalhoArvoreB(cabecalho);

    insercaoArvoreBRecursiva(arquivo, rrnAtual, chave, 0, proxRrn, caminho, byteOffset, cabecalho);

    setStatusCabecalhoArvoreB(cabecalho, '1');
    escreverCabecalhoArvoreB(arquivo, cabecalho);

    apagarCabecalhoArvoreB(cabecalho);
    free(caminho);
}