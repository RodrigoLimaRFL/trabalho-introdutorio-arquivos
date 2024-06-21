#include "registroArvoreB.h"

struct _registroArvoreB {
    int alturaNo;
    int nroChaves;
    int chaves[ORDEM_ARVORE_B - 1];
    long long int descendentes[ORDEM_ARVORE_B];
};

// cria um registro de árvore B com os valores padrao
REGISTRO_ARVORE_B *criarRegistroArvoreBVazio()
{
    REGISTRO_ARVORE_B *registro = malloc(sizeof(REGISTRO_ARVORE_B));
    registro->alturaNo = 0;
    registro->nroChaves = 0;
    for (int i = 0; i < ORDEM_ARVORE_B - 1; i++)
    {
        registro->chaves[i] = -1;
    }
    for (int i = 0; i < ORDEM_ARVORE_B; i++)
    {
        registro->descendentes[i] = -1;
    }

    return registro;
}

// insere uma chave no registro de árvore B
bool inserirChaveRegistroArvoreB(REGISTRO_ARVORE_B *registro, int chave)
{
    if (registro->nroChaves == ORDEM_ARVORE_B - 1) // se o registro estiver cheio
    {
        return false;
    }
    else if (registro->nroChaves == 0) // se o registro estiver vazio
    {
        registro->chaves[0] = chave;
        registro->nroChaves++;
    }
    else // se o registro não estiver vazio nem cheio
    {
        int i = registro->nroChaves - 1;
        while (i >= 0 && registro->chaves[i] > chave) // insere em ordem
        {
            registro->chaves[i + 1] = registro->chaves[i];
            i--;
        }
        registro->chaves[i + 1] = chave;
        registro->nroChaves++;
    }

    return true;
}

// remove uma chave do registro de árvore B
bool removerChaveRegistroArvoreB(REGISTRO_ARVORE_B *registro, int chave)
{
    if (registro->nroChaves == 0) // se o registro estiver vazio
    {
        return false;
    }
    else
    {
        int i = 0;
        while (i < registro->nroChaves && registro->chaves[i] != chave) // procura a chave
        {
            i++;
        }
        if (i == registro->nroChaves) // nao achou a chave
        {
            return false;
        }
        else
        {
            for (int j = i; j < registro->nroChaves - 1; j++)
            {
                registro->chaves[j] = registro->chaves[j + 1]; // reposiciona as chaves
            }
            registro->nroChaves--;
        }
    }

    return true;
}

// insere um descendente no registro de árvore B
bool inserirDescendenteRegistroArvoreB(REGISTRO_ARVORE_B *registro, long long int descendente, int chaveDescendente)
{
    if (!registro || registro->nroChaves == 0)
    {
        return false;
    }

    int i = 0;

    while (i < registro->nroChaves && registro->chaves[i] < chaveDescendente) // acha a posicao do descendente
    {
        if(registro->chaves[i] == chaveDescendente) // se a chave ja existe
        {
            return false;
        }
        i++;
    }

    if(registro->descendentes[i] != -1) // se a posicao ja esta ocupada
    {
        return false;
    }

    registro->descendentes[i] = descendente; // insere o descendente na posicao em que Ci < chaveDescendente < Ci+1

    return true;
}

bool removerDescendenteRegistroArvoreB(REGISTRO_ARVORE_B *registro, long long int descendente)
{
    if (registro->nroChaves == 0)
    {
        return false;
    }
    
    int i = 0;

    while (i < registro->nroChaves && registro->descendentes[i] != descendente) // acha a posicao do descendente
    {
        i++;
    }

    if(i == ORDEM_ARVORE_B) // nao achou o descendente
    {
        return false;
    }

    registro->descendentes[i] = -1; // remove o descendente

    return true;
}

int getAlturaNoRegistroArvoreB(REGISTRO_ARVORE_B *registro)
{
    if (registro == NULL)
    {
        return -1;
    }
    
    int alturaNo = registro->alturaNo;

    return alturaNo;
}

bool setAlturaNoRegistroArvoreB(REGISTRO_ARVORE_B *registro, int alturaNo)
{
    if (registro == NULL)
    {
        return false;
    }
    else
    {
        registro->alturaNo = alturaNo;
    }

    return true;
}

int getNroChavesRegistroArvoreB(REGISTRO_ARVORE_B *registro)
{
    if (registro == NULL)
    {
        return -1;
    }
    
    int nroChaves = registro->nroChaves;

    return nroChaves;
}

bool apagarRegistroArvoreB(REGISTRO_ARVORE_B *registro)
{
    if (registro == NULL)
    {
        return false;
    }
    else
    {
        free(registro);
    }

    return true;
}

bool imprimirRegistroArvoreB(REGISTRO_ARVORE_B *registro)
{
    if (registro == NULL)
    {
        return false;
    }
    else
    {
        printf("Altura: %d\n", registro->alturaNo);
        printf("Nro chaves: %d\n", registro->nroChaves);
        printf("Chaves: ");
        for (int i = 0; i < registro->nroChaves; i++)
        {
            printf("%d ", registro->chaves[i]);
        }
        printf("\n");
        printf("Descendentes: ");
        for (int i = 0; i < registro->nroChaves + 1; i++)
        {
            printf("%lld ", registro->descendentes[i]);
        }
        printf("\n");
    }

    return true;
}