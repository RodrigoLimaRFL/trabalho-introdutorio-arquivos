#ifndef ESCREVE_BIN_H
    #define ESCREVE_BIN_H
    #include "registro.h"
    #include "cabecalho.h"

    void lerCabecalhoFromBin2(FILE *file, CABECALHO *cabecalho);
    void lerRegistroFromBin2(FILE *file, REGISTRO *registro);
    CABECALHO *getCabecalhoFromBin2(char *filePath);
    void imprimeRegistrosFromBin(char *filePath);
    int imprimeRegistro(REGISTRO *registro);
    void imprimeRegistrosBuscados(char *arquivo);
    void removerRegistrosBuscados(char *arquivo);
#endif