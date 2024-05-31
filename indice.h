#ifndef INDICE_H
    #define INDICE_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <stdbool.h>
        #include "registroIndice.h"

        typedef struct _lista LISTA_INDICE;

        LISTA_INDICE *criarLista();
        REGISTRO_INDICE *getRegistro(LISTA_INDICE *lista, int index);
        int getTamanho(LISTA_INDICE *lista);
        bool adicionarRegistro(LISTA_INDICE *lista, REGISTRO_INDICE *registro);
        bool modificarRegistro(LISTA_INDICE *lista, int index, REGISTRO_INDICE *novoRegistro);
        REGISTRO_INDICE *buscarRegistro(LISTA_INDICE *lista, int id);
        void removerRegistro(LISTA_INDICE *lista, int index);
        bool apagarLista(LISTA_INDICE *lista);
        void imprimirLista(LISTA_INDICE *lista);
#endif

