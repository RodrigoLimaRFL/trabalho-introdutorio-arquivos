#ifndef ARVOREBDOIS_H
    #define ARVOREBDOIS_H

    #include "registroArvoreB.h"
    #include "cabecalhoArvoreB.h"

    void imprimirArvoreBGraphviz(FILE *arquivo);
    void inserirArvoreB(FILE *arquivo, int chave, long long int byteOffset);

#endif