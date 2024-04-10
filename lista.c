#include "lista.h"

struct lista_ = {
  int tamanho,
  REGISTRO *registros,
}

LISTA *criarLista() {
  LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
  LISTA->tamanho = 0;

  return lista;
}