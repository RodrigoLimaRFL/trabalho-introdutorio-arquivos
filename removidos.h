#ifndef REMOVIDOS_H
    #define REMOVIDOS_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <stdbool.h>
        #include "indice.h"
        #include "cabecalho.h"
        #include "escreveBin.h"
        #include "indice.h"
        #include "interpreta-bin.h"

        typedef struct _removidos REMOVIDOS;
        REMOVIDOS *criarListaRemovidos(FILE *file);
#endif