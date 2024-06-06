#include "removidos.h"

struct _removidos {
  LISTA_INDICE *lista;
  int *tamanhos;
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

REMOVIDOS *criarListaRemovidosVazia() {
  REMOVIDOS *removidos = malloc(sizeof(REMOVIDOS));
  removidos->lista = criarListaIndice();
  removidos->tamanhos = malloc(sizeof(int) * 1000);

  return removidos;
}

// cria uma lista de registros removidos a partir de um arquivo binario
REMOVIDOS *criarListaRemovidos(FILE *file) {
  printf("removidos 1\n");

  CABECALHO *cabecalho = getCabecalhoFromBin(file);

  printf("removidos 10338\n");

  REMOVIDOS *removidos = criarListaRemovidosVazia();

  printf("removidos 2\n");

  if(fseek(file, 0, SEEK_END) != 0) {
    printf("erro ao mover ponteiro 2\n");
  }
  long finalArquivo = ftell(file);
  printf("finalArquivo: %ld\n", finalArquivo);

  printf("3\n");

  long long proxByteOffset = getTopo(cabecalho);

  while(proxByteOffset != -1 && proxByteOffset < finalArquivo) {
    printf("proxByteOffset: %lld\n", proxByteOffset);
    REGISTRO *registro = lerRegistroFromBin(proxByteOffset, file);
    printf("tamanho: %d\n", get_tamanhoRegistro(registro));

    if(get_removido(registro) == '1') {
      REGISTRO_INDICE *registroIndice = criarRegistroIndice();
      setIndexRegistroIndice(registroIndice, get_id(registro));
      setByteOffsetRegistroIndice(registroIndice, proxByteOffset);

      adicionarRegistroRemovido(removidos, registroIndice, get_tamanhoRegistro(registro));
    }

    proxByteOffset = get_prox(registro);
    printf("proxByteOffset: %lld\n\n", proxByteOffset);
  }

  return removidos;
}

void atualizarProxRegistrosRemovidos(int byteOffsetRegistroInserido, int proxRegistroAntigo, REMOVIDOS *removidos, FILE *file) {
  CABECALHO *cabecalho = getCabecalhoFromBin(file);

  fseek(file, 0, SEEK_END);
  int finalArquivo = ftell(file);

  int proxByteOffset = getTopo(cabecalho);
  proxByteOffset += 25; // pula o cabecalhos

  while(proxByteOffset != -1 && proxByteOffset < finalArquivo) {
    REGISTRO *registro = lerRegistroFromBin(proxByteOffset, file);

    if(get_removido(registro) == '1') {
      REGISTRO_INDICE *registroIndice = criarRegistroIndice();
      setIndexRegistroIndice(registroIndice, get_id(registro));
      setByteOffsetRegistroIndice(registroIndice, proxByteOffset);

      adicionarRegistroRemovido(removidos, registroIndice, get_tamanhoRegistro(registro));
    }

    proxByteOffset = get_prox(registro);
  }
}

int getTamanhoListaRemovidos(REMOVIDOS *removidos) {
  return getTamanhoListaIndice(removidos->lista);
}

void removerRegistroRemovidoPosicao(REMOVIDOS *removidos, int posicao) {
  removerRegistroIndice(removidos->lista, posicao);

  for(int i = posicao; i < getTamanhoListaIndice(removidos->lista); i++) {
    removidos->tamanhos[i] = removidos->tamanhos[i + 1];
  }
}

void removerRegistroRemovido(REMOVIDOS *removidos, int id) {
  int posicao = buscarPosicaoRegistroIndice(removidos->lista, id);

  if(posicao == -1) {
    return;
  }

  removerRegistroRemovidoPosicao(removidos, posicao);
}

void removerRegistroRemovidoEAtualizarArquivo(REMOVIDOS *removidos, int id, FILE *file) {
  int posicao = buscarPosicaoRegistroIndice(removidos->lista, id);

  if(posicao == -1) {
    return;
  }

  int tamanhoLista = getTamanhoListaIndice(removidos->lista);
  const int byteProx = 5;
  CABECALHO *cabecalho = getCabecalhoFromBin(file);

  setStatus(cabecalho, '0');
  
  if(tamanhoLista == 1) { // lista so tem um elemento removido
    setTopo(cabecalho, -1);
    writeTopoCabecalho(cabecalho, file);
  }
  else if(posicao == 0) // removendo o primeiro elemento
  {
    REGISTRO_INDICE *registroIndice = getRegistroIndice(removidos->lista, 1);
    long long int byteOffset = getByteOffsetRegistroIndice(registroIndice);

    setTopo(cabecalho, byteOffset);
    writeTopoCabecalho(cabecalho, file);
  }
  else if(posicao == tamanhoLista - 1) // removendo o ultimo elemento
  {
    REGISTRO_INDICE *registroIndice = getRegistroIndice(removidos->lista, posicao - 1);
    long long int byteOffset = getByteOffsetRegistroIndice(registroIndice);

    REGISTRO *registro = lerRegistroFromBin(byteOffset, file);
    set_prox(registro, -1);
    int prox = -1;
    
    byteOffset += byteProx;
    fseek(file, byteOffset, SEEK_SET);
    fwrite(&prox, sizeof(int), 1, file);
  }
  else
  {
    REGISTRO_INDICE *registroIndiceAnterior = getRegistroIndice(removidos->lista, posicao - 1);
    REGISTRO_INDICE *registroIndiceProximo = getRegistroIndice(removidos->lista, posicao + 1);

    long long int byteOffsetAnterior = getByteOffsetRegistroIndice(registroIndiceAnterior);
    long long int byteOffsetProximo = getByteOffsetRegistroIndice(registroIndiceProximo);

    REGISTRO *registro = lerRegistroFromBin(byteOffsetAnterior, file);
    set_prox(registro, byteOffsetProximo);

    byteOffsetAnterior += byteProx;
    fseek(file, byteOffsetAnterior, SEEK_SET);
    fwrite(&byteOffsetProximo, sizeof(int), 1, file);
  }

  removerRegistroRemovidoPosicao(removidos, posicao);
}

int getTamanhoById(REMOVIDOS *removidos, int id) {
  int posicao = buscarPosicaoRegistroIndice(removidos->lista, id);

  if(posicao == -1) {
    return -1;
  }

  return removidos->tamanhos[posicao];
}

long long int getBestFitByteOffset(REMOVIDOS *removidos, int tamanho) {
  int left = 0;
  int right = getTamanhoListaIndice(removidos->lista) - 1;

  int middle = (left + right) / 2;

  while(left < right) {
    if(removidos->tamanhos[middle] < tamanho) {
      right = middle;
    } else {
      left = middle + 1;
    }

    middle = (left + right) / 2;
  }

  long long int byteOffset = getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, middle));

  return byteOffset;
}

long long int getBestFitAndFreeSpace(REMOVIDOS *removidos, int tamanho) {
  int left = 0;
  int right = getTamanhoListaIndice(removidos->lista) - 1;

  int middle = (left + right) / 2;

  while(left < right) {
    if(removidos->tamanhos[middle] < tamanho) {
      right = middle;
    } else {
      left = middle + 1;
    }

    middle = (left + right) / 2;
  }

  long long int byteOffset = getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, middle));

  removerRegistroRemovidoPosicao(removidos, middle);

  return byteOffset;
}