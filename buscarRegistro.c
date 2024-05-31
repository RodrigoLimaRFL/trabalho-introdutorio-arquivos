#include "buscarRegistro.h"
#define BYTEOFFSET 25 // primeiro byte apos cabecalho

REGISTRO *buscarRegistro(char *chave, char *operacao, CABECALHO *cabecalho, FILE *file)
{
    int numRegistros = getNroRegArq(cabecalho) + getNroRem(cabecalho);

    if(numRegistros == 0)
    {
        printf("Registro inexistente\n\n");
        return NULL;
    }

    if(strcmp(operacao, "id") == 0)
    {
        return buscarId(chave, numRegistros, file);
    }
    else if(strcmp(operacao, "nome") == 0)
    {
        return buscarNome(chave, numRegistros, file);
    }
    else if(strcmp(operacao, "idade") == 0)
    {
        return buscarIdade(chave, numRegistros, file);
    }
    else if(strcmp(operacao, "nomeClube") == 0)
    {
        return buscarNomeClube(chave, numRegistros, file);
    }
    else if(strcmp(operacao, "nacionalidade") == 0)
    {
        return buscarNacionalidade(chave, numRegistros, file);
    }
    else
    {
        printf("Campo invalido\n");
        return NULL;
    }
}

REGISTRO *buscarId(char *id, int numRegistros, FILE *file)
{
    REGISTRO *registro = criarRegistroNulo();
    int byteOffset = BYTEOFFSET;
    fseek(file, byteOffset, SEEK_SET);

    int idInt = atoi(id);

    for(int i = 0; i < numRegistros; i++)
    {
        registro = lerRegistroFromBin(byteOffset, file);
        if(get_id(registro) == idInt)
        {
            return registro;
        }
    }

    return NULL;
}

REGISTRO *buscarNome(char *nome, int numRegistros, FILE *file)
{
    REGISTRO *registro = criarRegistroNulo();
    int byteOffset = BYTEOFFSET;
    fseek(file, byteOffset, SEEK_SET);

    for(int i = 0; i < numRegistros; i++)
    {
        registro = lerRegistroFromBin(byteOffset, file);
        if(strcmp(get_nome(registro), nome) == 0)
        {
            return registro;
        }
    }

    return NULL;
}

REGISTRO *buscarIdade(char *idade, int numRegistros, FILE *file)
{
    REGISTRO *registro = criarRegistroNulo();
    int byteOffset = BYTEOFFSET;
    fseek(file, byteOffset, SEEK_SET);

    int idadeInt = atoi(idade);

    for(int i = 0; i < numRegistros; i++)
    {
        registro = lerRegistroFromBin(byteOffset, file);
        if(get_idade(registro) == idadeInt)
        {
            return registro;
        }
    }

    return NULL;
}

REGISTRO *buscarNomeClube(char *nomeClube, int numRegistros, FILE *file)
{
    REGISTRO *registro = criarRegistroNulo();
    int byteOffset = BYTEOFFSET;
    fseek(file, byteOffset, SEEK_SET);

    for(int i = 0; i < numRegistros; i++)
    {
        registro = lerRegistroFromBin(byteOffset, file);
        if(strcmp(get_nomeClube(registro), nomeClube) == 0)
        {
            return registro;
        }
    }

    return NULL;
}

REGISTRO *buscarNacionalidade(char *nacionalidade, int numRegistros, FILE *file)
{
    REGISTRO *registro = criarRegistroNulo();
    int byteOffset = BYTEOFFSET;
    fseek(file, byteOffset, SEEK_SET);

    for(int i = 0; i < numRegistros; i++)
    {
        registro = lerRegistroFromBin(byteOffset, file);
        if(strcmp(get_nacionalidade(registro), nacionalidade) == 0)
        {
            return registro;
        }
    }

    return NULL;
}