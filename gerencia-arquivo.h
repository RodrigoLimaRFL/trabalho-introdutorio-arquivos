typedef struct dados DADOS;

LISTA *lerCsv(char *nomeArquivo);
void lerLinha(char *linha, DADOS *dados);
void teste();
void escreveBinario(LISTA *lista, char *binario);