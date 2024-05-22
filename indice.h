#ifndef INDICE_H
    #define INDICE_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <stdbool.h>

        typedef struct _registro_dados REGISTRO_DADOS;
        typedef struct _indice INDICE;

        REGISTRO_DADOS *criarRegistroDados();
        INDICE *criarIndice();
        void apagarRegistroDados(REGISTRO_DADOS *registro);
        void apagarIndice(INDICE *indice);
        void setStatusIndice(INDICE *indice, char status);
        void setQuantidadeIndice(INDICE *indice, int quantidade);
        void setDadosIndice(INDICE *indice, REGISTRO_DADOS *dados);
        char getStatusIndice(INDICE *indice);
        int getQuantidadeIndice(INDICE *indice);
        REGISTRO_DADOS *getDadosIndice(INDICE *indice);
        void setIndexRegistroIndice(REGISTRO_DADOS *registro, int index);
        void setByteOffsetRegistroIndice(REGISTRO_DADOS *registro, long long int byteOffset);
        int getIndexRegistroIndice(REGISTRO_DADOS *registro);
        long long int getByteOffsetRegistroIndice(REGISTRO_DADOS *registro);
        bool binarySearchIndice(INDICE *indice, int index, int *pos);
        void insertRegistroIndice(INDICE *indice, REGISTRO_DADOS *registro);
        void shiftRegistrosRight(INDICE *indice, int pos);
        void printRegistrosIndice(INDICE *indice);
#endif

