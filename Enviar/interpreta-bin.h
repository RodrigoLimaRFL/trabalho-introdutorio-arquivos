#ifndef INTERPRETA_BIN_H
    #define INTERPRETA_BIN_H
    #include "lista.h"
    #include "registro.h"
    #include "cabecalho.h"

    CABECALHO *getCabecalhoFromBin(char *filePath);
    LISTA *getRegistrosFromBin(char *filePath);
#endif