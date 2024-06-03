#ifndef ESCREVE_BIN_H
    #define ESCREVE_BIN_H
    #include "registro.h"
    #include "cabecalho.h"
    #include "removidos.h"
    #include "cabecalho.h"
    #include "funcoes_fornecidas.h"
    #include "interpreta-bin.h"
    
    void imprimeRegistrosFromBin(char *filePath);
    int imprimeRegistro(REGISTRO *registro);
    void imprimeRegistrosBuscados(char *arquivo);
    void removerRegistrosBuscados(char *arquivo, REMOVIDOS *listaRemovidos);
#endif