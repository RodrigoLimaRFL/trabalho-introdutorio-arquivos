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









#include "lista.h"

typedef struct no_ NO;

struct no_ {
  ITEM *item;
  NO *prox;
};

struct lista_ {
  NO *inicio;
  NO *fim;
  int tamanho;
};

LISTA *lista_criar(void) {
  LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;

  return lista;
}

bool lista_inserir(LISTA *lista, ITEM *item) {
  if(!lista_cheia(lista)) {
    NO *no = (NO *) malloc(sizeof(NO));
    no->item = item;
    no->prox = NULL;

    if(lista_vazia(lista)) {
      lista->inicio = no;
    } else {
      lista->fim->prox = no;
    }
    lista->fim = no;
    lista->tamanho++;

    return true;
  }
  return false;
}

ITEM *lista_remover(LISTA *lista, int chave) {
  int i;

  if(!lista_vazia(lista)) {
    NO *noAtual = lista->inicio;
    NO *noAnterior = NULL;
    ITEM *item;
    int tamanho = lista_tamanho(lista);

    for(i=0; i<tamanho; i++) {
      if(item_get_chave(noAtual->item) == chave) {
        if(noAtual == lista->inicio) {
          lista->inicio = noAtual->prox;
        } else {
          noAnterior->prox = noAtual->prox;
        }
        if(noAtual == lista->fim) {
          lista->fim = noAnterior;
        }
        item = noAtual->item;
        free(noAtual);
        lista->tamanho--;

        return item;
      }
      noAnterior = noAtual;
      noAtual = noAtual->prox;
    }
  } 
  return NULL;
}

bool lista_apagar(LISTA **lista) {
  if(*lista != NULL) {
    int i;
    NO *noAtual = (*lista)->inicio;
    NO *noAux;
    int tamanho = lista_tamanho(*lista);

    for(i=0; i<tamanho; i++) {
      noAux = noAtual;
      item_apagar(&(noAtual->item));
      free(noAtual);
      noAtual = noAux->prox;
    }

    free(*lista);
    *lista = NULL;

    return true;
  }
  return false;
}

ITEM *lista_busca(LISTA *lista, int chave) {
  int i;
  NO *noAtual = lista->inicio;
  int tamanho = lista_tamanho(lista);

  for(i=0; i<tamanho; i++) {
    if(item_get_chave(noAtual->item) == chave) {
      return noAtual->item;
    }
    noAtual = noAtual->prox;
  }
  return NULL;
}

int lista_tamanho(LISTA *lista) {
  return lista->tamanho;
}

bool lista_vazia(LISTA *lista) {
  if(lista != NULL && lista->inicio != NULL) {
    return false;
  }
  return true;
}

bool lista_cheia(LISTA *lista) {
  return false;
}

void lista_imprimir(LISTA *lista) {
  int i;
  NO *noAtual = lista->inicio;
  int tamanho = lista_tamanho(lista);

  for(i=0; i<tamanho; i++) {
    printf("[%d]; ", item_get_chave(noAtual->item));
    noAtual = noAtual->prox;
  }
  printf("\n");
}

bool lista_inverter(LISTA **lista) {
  if(*lista != NULL) {
    int i;
    NO *noAnterior = NULL;
    NO *noAtual = (*lista)->inicio;
    NO *noProx = NULL;

    for(i=0; i<lista_tamanho(*lista); i++) {
      noProx = noAtual->prox;
      noAtual->prox = noAnterior;
      noAnterior = noAtual;
      noAtual = noProx;
    }

    (*lista)->inicio = noAnterior;
    return true;
  }
  return false;
}