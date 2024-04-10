#include "lista.h"

struct lista_ = {
  int tamanho,
  REGISTRO **registros,
}

LISTA *criarLista() {
  LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
  LISTA->tamanho = 0;
  lista->registros = (REGISTRO **) malloc(sizeof((REGISTRO *) * 1000));

  return lista;
}

int adicionarRegistro(REGISTRO *registro) {
  lista->registros[tamanho] = registro;
  return 1;
}

int modificarRegistro(int index, REGISTRO *novoRegistro) {
  lista->registros[index] = novoRegistro;
  return 1;
}

int buscarRegistro(int id) {
  for(int i=0; i<lista->tamanho; i++) {
    if((*(lista->registros[i])).id == id) {
      return i;
    }
  }
  return -1;
}

int removerRegistro(int index) {
  for(int i=index; i<lista->tamanh-1; i++) {
    lista->registros[i] = lista->registros[i+1];
  }

  free(lista->registros[tamanho]);
  lista->tamanho--;
}

int apagarLista(LISTA *lista) {
  for(int i=0; i<lista->tamanho; i++) {
    free(lista->registros[i]);
  }

  free(lista);
}