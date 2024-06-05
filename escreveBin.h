#ifndef ESCREVE_BIN_H
    #define ESCREVE_BIN_H
    #include "registro.h"
    #include "removidos.h"
    #include "funcoes_fornecidas.h"
    
    void imprimeRegistrosFromBin(char *filePath);
    int imprimeRegistro(REGISTRO *registro);
    void imprimeRegistrosBuscados(char *arquivo);
    void removerRegistrosBuscados(FILE *file, REMOVIDOS *listaRemovidos, LISTA_INDICE *listaIndices);
    void removeById(int id, LISTA_INDICE *listaIndices, FILE *file, REMOVIDOS *listaRemovidos);
    bool escreverRegistro(REGISTRO *registro, int byteOffset, int tamRegistroAtual, FILE *arquivoBin);
#endif