#ifndef ESCREVE_BIN_H
    #define ESCREVE_BIN_H
    #include "registro.h"
    #include "removidos.h"
    #include "funcoes_fornecidas.h"
    
    void imprimeRegistrosFromBin(char *filePath);
    int imprimeRegistro(REGISTRO *registro);
    void imprimeRegistrosBuscados(char *arquivo);
    void removerRegistrosBuscados(char *arquivoBin, char *arquivoIndice);
    void removeById(int id, LISTA_INDICE *listaIndices, FILE *file, REMOVIDOS *listaRemovidos, CABECALHO *cabecalho);
    bool escreverRegistro(REGISTRO *registro, int byteOffset, int tamRegistroAtual, FILE *arquivoBin);
#endif