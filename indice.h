#ifndef INDICE_H
    #define INDICE_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <stdbool.h>
        #include "registroIndice.h"
        #include "escreveBin.h"

        typedef struct _lista LISTA_INDICE;

<<<<<<< HEAD
        LISTA_INDICE *criarLista();
        REGISTRO_INDICE *getRegistro(LISTA_INDICE *lista, int index);
        int getTamanho(LISTA_INDICE *lista);
        bool adicionarRegistro(LISTA_INDICE *lista, REGISTRO_INDICE *registro);
        bool adicionarRegistroOrdenado(LISTA_INDICE *lista, REGISTRO_INDICE *registro, FILE *file);
        bool modificarRegistro(LISTA_INDICE *lista, int index, REGISTRO_INDICE *novoRegistro);
        REGISTRO_INDICE *buscarRegistro(LISTA_INDICE *lista, int id);
        void removerRegistro(LISTA_INDICE *lista, int index);
        bool apagarLista(LISTA_INDICE *lista);
        void imprimirLista(LISTA_INDICE *lista);
        REGISTRO *buscarRegistroOffset(long long offset, FILE *file);
=======
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
>>>>>>> refs/remotes/origin/main
#endif

