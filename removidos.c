#include "removidos.h"

struct _removidos {
  LISTA_INDICE *lista;
  int *tamanhoRegistro;
};

REMOVIDOS *criarListaRemovidos(char *filePath) {
  CABECALHO *cabecalho = getCabecalhoFromBin2(filePath);

  REMOVIDOS *removidos = criarLista();
  FILE *file = fopen(filePath, "rb");

  if (file == NULL) // verifica se ocorreu um erro ao abrir o arquivo no modo leitura
  {
    printf("Falha no processamento do arquivo.");
    return NULL;
  }

  int proxyByteOffset = getProxByteOffset(cabecalho);
  fseek(file, proxyByteOffset, SEEK_SET);

  while(proxyByteOffset != -1) {
    REGISTRO *registro = criarRegistroNulo(); // cria um registro com os valores iniciais
    lerRegistroFromBin2(file, registro); // salva os valores do registro do arquivo binário no registro criado
    
    adicionarRegistro(removidos, registro);
    fseek(file, get_prox(registro), SEEK_SET);
  }

  return removidos;
}