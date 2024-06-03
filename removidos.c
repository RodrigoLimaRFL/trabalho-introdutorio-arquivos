#include "removidos.h"

struct _removidos {
  LISTA_INDICE *lista;
  int tamanhos[1000];
};


void shiftElementosListaRemovidosRight(REMOVIDOS *removidos, int pos) {
  for(int i = getTamanhoListaIndice(removidos->lista); i > pos; i--) {
    REGISTRO_INDICE *registro = getRegistroIndice(removidos->lista, i - 1);
    setRegistroListaIndice(removidos->lista, i, registro);
    removidos->tamanhos[i] = removidos->tamanhos[i - 1];
  }
}

// adiciona um novo registro na lista em ordem de tamanho
void adicionarRegistroRemovido(REMOVIDOS *removidos, REGISTRO_INDICE *registroIndice, int tamanho) {
  int right = getTamanhoListaIndice(removidos->lista);
  int left = 0;
  
  int middle = (left + right) / 2;

  while(left < right) {
    if(removidos->tamanhos[middle] < tamanho) {
      right = middle;
    } else {
      left = middle + 1;
    }

    middle = (left + right) / 2;
  }

  shiftElementosListaRemovidosRight(removidos, middle);

  setRegistroListaIndice(removidos->lista, middle, registroIndice);
  removidos->tamanhos[middle] = tamanho;
}

// cria uma lista de registros removidos a partir de um arquivo binario
REMOVIDOS *criarListaRemovidos(FILE *file) {
  CABECALHO *cabecalho = getCabecalhoFromBin(file);

  REMOVIDOS *removidos;
  removidos->lista = criarLista();

  int proxByteOffset = getTopo(cabecalho);

  while(proxByteOffset != -1) {
    REGISTRO *registro = lerRegistroFromBin(proxByteOffset, file);

    if(getRemovido(registro) == '1') {
      REGISTRO_INDICE *registroIndice = criarRegistroIndice();
      setIndexRegistroIndice(registroIndice, getId(registro));
      setByteOffsetRegistroIndice(registroIndice, proxByteOffset);

      adicionarRegistroRemovido(removidos, registroIndice, get_tamanhoRegistro(registro));
    }

    proxByteOffset = get_prox(registro);
  }

  return removidos;
}

int getTamanhoListaRemovidos(REMOVIDOS *removidos) {
  return getTamanhoListaIndice(removidos->lista);
}

void removerRegistroRemovido(REMOVIDOS *removidos, int id) {
  int posicao = buscarPosicaoRegistroIndice(removidos->lista, id);

  if(posicao == -1) {
    return;
  }

  REGISTRO_INDICE *registro = getRegistroIndice(removidos->lista, posicao);
  removerRegistroIndice(removidos->lista, posicao);

  for(int i = posicao; i < getTamanhoListaIndice(removidos->lista); i++) {
    removidos->tamanhos[i] = removidos->tamanhos[i + 1];
  }
}

int getTamanhoById(REMOVIDOS *removidos, int id) {
  int posicao = buscarPosicaoRegistroIndice(removidos->lista, id);

  if(posicao == -1) {
    return -1;
  }

  return removidos->tamanhos[posicao];
}