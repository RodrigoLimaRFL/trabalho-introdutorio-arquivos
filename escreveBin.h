#ifndef ESCREVE_BIN_H
    #define ESCREVE_BIN_H
    #include "registro.h"
    #include "removidos.h"
    #include "funcoes_fornecidas.h"
    #include "criarIndice.h"
    #include "cabecalho.h"
    #include "arvoreB.h"
    
    void imprimeRegistrosFromBin(char *filePath);
    int imprimeRegistro(REGISTRO *registro);
    void imprimeRegistrosBuscados(char *arquivo, int buscaId, char *nomeArquivoArvoreB);
    void imprimirRegistrosPorCampos(FILE *file, CABECALHO *cabecalho, int buscaId, char *nomeArquivoArvoreB, int i);
    void imprimirIdArvoreB(int id, FILE *file, char *nomeArquivoArvoreB, int i, int buscaMinuscula);
    long long int buscarRegistroIdRec(FILE *fileArvoreB, int id, int rrnAtual);
    void removerRegistrosBuscados(char *arquivoBin, char *arquivoIndice);
    void removeById(int id, LISTA_INDICE *listaIndices, FILE *file, FILE *fileIndices, REMOVIDOS *listaRemovidos, CABECALHO *cabecalho, char* arquivoIndice);
    bool escreverRegistro(REGISTRO *registro, int byteOffset, int tamRegistroAtual, FILE *arquivoBin);
    bool criarArquivoArvoreB(char *arquivoBin, char *arquivoArvB);
#endif