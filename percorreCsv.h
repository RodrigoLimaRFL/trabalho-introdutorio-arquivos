#ifndef PERCORRECSV_H
    #define PERCORRECSV_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "gerencia-arquivo.h"
    #include "lista.h"
    #include "cabecalho.h"

    LISTA *lerCsvEscreveBin(char *nomeArquivoCsv, char *nomeArquivoBin);

#endif