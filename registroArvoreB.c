#include "registroArvoreB.h"

struct _registroArvoreB {
    int alturaNo;
    int nroChaves;
    int chaves[ORDEM_ARVORE_B - 1];
    long long int descendentes[ORDEM_ARVORE_B];
};

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

bool inserirChaveRegistroArvoreB(REGISTRO_ARVORE_B *registro, int chave)
{
    if (registro->nroChaves == 0)
    {
        registro->chaves[0] = chave;
        registro->nroChaves++;
    }
    else if (registro->nroChaves == ORDEM_ARVORE_B - 1)
    {
        return false;
    }
    else
    {
        int i = registro->nroChaves - 1;
        while (i >= 0 && registro->chaves[i] > chave)
        {
            registro->chaves[i + 1] = registro->chaves[i];
            i--;
        }
        registro->chaves[i + 1] = chave;
        registro->nroChaves++;
    }

    return true;
}

bool removerChaveRegistroArvoreB(REGISTRO_ARVORE_B *registro, int chave)
{
    if (registro->nroChaves == 0)
    {
        return false;
    }
    else
    {
        int i = 0;
        while (i < registro->nroChaves && registro->chaves[i] != chave)
        {
            i++;
        }
        if (i == registro->nroChaves)
        {
            return false;
        }
        else
        {
            for (int j = i; j < registro->nroChaves - 1; j++)
            {
                registro->chaves[j] = registro->chaves[j + 1];
            }
            registro->nroChaves--;
        }
    }

    return true;
}

bool inserirDescendenteRegistroArvoreB(REGISTRO_ARVORE_B *registro, long long int descendente, int chaveDescendente)
{
    if (registro->nroChaves == 0)
    {
        return false;
    }
    else
    {
        int i = 0;
        while (i < registro->nroChaves && registro->chaves[i] < chaveDescendente)
        {
            i++;
        }
        if (i == registro->nroChaves)
        {
            return false;
        }
        else
        {
            for (int j = registro->nroChaves; j > i; j--)
            {
                registro->descendentes[j] = registro->descendentes[j - 1];
            }
            registro->descendentes[i] = descendente;
        }
    }

    return true;
}

bool removerDescendenteRegistroArvoreB(REGISTRO_ARVORE_B *registro, long long int descendente)
{
    if (registro->nroChaves == 0)
    {
        return false;
    }
    else
    {
        int i = 0;
        while (i < registro->nroChaves && registro->descendentes[i] != descendente)
        {
            i++;
        }
        if (i == registro->nroChaves)
        {
            return false;
        }
        else
        {
            for (int j = i; j < registro->nroChaves - 1; j++)
            {
                registro->descendentes[j] = registro->descendentes[j + 1];
            }
        }
    }

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