#ifndef CRIAR_INDICE_H
    #define CRIAR_INDICE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    #include "indice.h"
    #include "cabecalho.h"
    #include "registroIndice.h"
    #include "interpreta-bin.h"

    bool lerBinCriarIndice(FILE *arquivoBinario, char *arquivoIndice);
#endif