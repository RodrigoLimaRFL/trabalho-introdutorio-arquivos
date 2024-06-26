#ifndef ARVOREB_H
    #define ARVOREB_H

    #include "registroArvoreB.h"
    #include "cabecalhoArvoreB.h"

    void imprimirArvoreBGraphviz(FILE *arquivo);
    void inserirArvoreB(FILE *arquivo, int chave, long long int byteOffset);

#endif