typedef struct dados DADOS;

#include "lista.h"

LISTA *lerCsv(char *nomeArquivo);
void lerLinha(char *linha, DADOS *dados);
void teste();
void escreveBinario(CABECALHO *cabecalho, LISTA *lista, char *binario);