#ifndef INDICE_H
    #define INDICE_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <stdbool.h>
        #include "registroIndice.h"
        #include "escreveBin.h"

        typedef struct _lista LISTA_INDICE;

        LISTA_INDICE *criarListaIndice();
        REGISTRO_INDICE *getRegistroIndice(LISTA_INDICE *lista, int index);
        int getTamanhoIndice(LISTA_INDICE *lista);
        bool adicionarRegistroIndice(LISTA_INDICE *lista, REGISTRO_INDICE *registro);
        bool adicionarRegistroOrdenadoIndice(LISTA_INDICE *lista, REGISTRO_INDICE *registro);
        bool modificarRegistroIndice(LISTA_INDICE *lista, int index, REGISTRO_INDICE *novoRegistro);
        REGISTRO_INDICE *buscarRegistroIndice(LISTA_INDICE *lista, int id);
        void removerRegistroIndice(LISTA_INDICE *lista, int index);
        bool apagarListaIndice(LISTA_INDICE *lista);
        void imprimirListaIndice(LISTA_INDICE *lista);
        bool carregarIndice(LISTA_INDICE *lista, FILE *file);
#endif

