#ifndef REMOVIDOS_H
    #define REMOVIDOS_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <stdbool.h>
        #include "indice.h"
        #include "interpreta-bin.h"

        typedef struct _removidos REMOVIDOS;
        REMOVIDOS *criarListaRemovidos(FILE *file);
        void adicionarRegistroRemovido(REMOVIDOS *removidos, REGISTRO_INDICE *registroIndice, int tamanho);
        void removerRegistroRemovido(REMOVIDOS *removidos, int id);
        void removerRegistroRemovidoEAtualizarArquivo(REMOVIDOS *removidos, int id, FILE *file);
        int getTamanhoById(REMOVIDOS *removidos, int id);
        long long int getBestFitByteOffset(REMOVIDOS *removidos, int tamanho);
        long long int getBestFitAndFreeSpace(REMOVIDOS *removidos, int tamanho);
#endif