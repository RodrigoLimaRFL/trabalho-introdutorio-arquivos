#include "removidos.h"

struct _removidos {
  LISTA_INDICE *lista;
  int tamanhoRegistro[1000];
};

REMOVIDOS *criarListaRemovidos(char *filePath) {
  CABECALHO *cabecalho = getCabecalhoFromBin2(filePath);

  REMOVIDOS *removidos;
  removidos->lista = criarLista();
  FILE *file = fopen(filePath, "rb");

  if (file == NULL) // verifica se ocorreu um erro ao abrir o arquivo no modo leitura
  {
    printf("Falha no processamento do arquivo.");
    return NULL;
  }

  int proxyByteOffset = getTopo(cabecalho);
  fseek(file, proxyByteOffset, SEEK_SET);

  int i=0;
  while(proxyByteOffset != -1) {
    REGISTRO *registro = criarRegistroNulo(); // cria um registro com os valores iniciais
    lerRegistroFromBin2(file, registro); // salva os valores do registro do arquivo binário no registro criado
    
    adicionarRegistro(removidos->lista, registro);
    proxyByteOffset = get_prox(registro);
    fseek(file, proxyByteOffset, SEEK_SET);
    removidos->tamanhoRegistro[i] = get_tamanhoRegistro(registro);
    i++;
  }

  return removidos;
}