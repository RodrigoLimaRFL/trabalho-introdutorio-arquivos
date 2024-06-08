#include "removidos.h"

struct _removidos {
  LISTA_INDICE *lista;
  int *tamanhos;
};

void apagarListaRemovidos(REMOVIDOS *removidos) {
  apagarListaIndice(removidos->lista);
  free(removidos->tamanhos);
  free(removidos);
}

void shiftElementosListaRemovidosRight(REMOVIDOS *removidos, int pos) {
  for(int i = getTamanhoListaIndice(removidos->lista); i > pos; i--) {
    REGISTRO_INDICE *registro = getRegistroIndice(removidos->lista, i - 1);
    setRegistroListaIndice(removidos->lista, i, registro);
    removidos->tamanhos[i] = removidos->tamanhos[i - 1];
  }
}

long long int getMaiorByteOffsetMenorQue(REMOVIDOS *removidos, int id) {
  int posicao = buscarPosicaoRegistroIndice(removidos->lista, id);
  
  if (posicao == -1) {
    return -2; // id não encontrado
  }

  long long int byteOffsetAtual = getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, posicao));
  long long int maiorByteOffset = -1;

  for (int i = 0; i < posicao; i++) {
    long long int byteOffset = getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, i));
    if (byteOffset < byteOffsetAtual && byteOffset > maiorByteOffset) {
      maiorByteOffset = byteOffset;
    }
  }

  return maiorByteOffset;
}

// adiciona um novo registro na lista em ordem de tamanho
void adicionarRegistroRemovido(REMOVIDOS *removidos, REGISTRO_INDICE *registroIndice, int tamanho) {
    int right = getTamanhoListaIndice(removidos->lista);
    int left = 0;
    
    while (left < right) {
        int middle = (left + right) / 2;
        if (removidos->tamanhos[middle] > tamanho) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }

    // Move elementos à direita para abrir espaço para o novo registro
    shiftElementosListaRemovidosRight(removidos, left);

    // Adiciona o novo registro na posição encontrada
    setRegistroListaIndice(removidos->lista, left, registroIndice);
    removidos->tamanhos[left] = tamanho;

    // Atualiza o tamanho da lista
    setTamanho(removidos->lista, getTamanhoListaIndice(removidos->lista) + 1);
}

REMOVIDOS *criarListaRemovidosVazia() {
  REMOVIDOS *removidos = malloc(sizeof(REMOVIDOS));
  removidos->lista = criarListaIndice();
  removidos->tamanhos = malloc(sizeof(int) * 1000);

  return removidos;
}

// cria uma lista de registros removidos a partir de um arquivo binario
REMOVIDOS *criarListaRemovidos(FILE *file) {
  CABECALHO *cabecalho = getCabecalhoFromBin(file);
  REMOVIDOS *removidos = criarListaRemovidosVazia();

  fseek(file, 0, SEEK_END);
  int finalArquivo = ftell(file);

  int proxByteOffset = getTopo(cabecalho);
  //proxByteOffset += 25; // pula o cabecalho
  
  int count = 0;

  // mudou aq
  while(proxByteOffset != -1 && proxByteOffset < finalArquivo) {
    REGISTRO *registro = lerRegistroFromBin(proxByteOffset, file);

    count++;

    if(get_removido(registro) == '1') {
      REGISTRO_INDICE *registroIndice = criarRegistroIndice();
      setIndexRegistroIndice(registroIndice, get_id(registro));
      setByteOffsetRegistroIndice(registroIndice, proxByteOffset);

      adicionarRegistroRemovido(removidos, registroIndice, get_tamanhoRegistro(registro));
    }

    proxByteOffset = get_prox(registro);

    REGISTRO *proxRegistro;

    if(proxByteOffset != -1 && proxByteOffset < finalArquivo)
      proxRegistro = lerRegistroFromBin(proxByteOffset, file);

    if(get_prox(proxRegistro) == -1 && get_removido(proxRegistro) == '1') {
      REGISTRO_INDICE *registroIndice = criarRegistroIndice();
      setIndexRegistroIndice(registroIndice, get_id(proxRegistro));
      setByteOffsetRegistroIndice(registroIndice, proxByteOffset);

      adicionarRegistroRemovido(removidos, registroIndice, get_tamanhoRegistro(proxRegistro));
      break;
    }

    free(proxRegistro);
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



void removerRegistroRemovidoEAtualizarArquivo(REMOVIDOS *removidos, int posicao, FILE *file) {
  REGISTRO *registro = buscarRegistroOffset(getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, posicao)) ,file);

  if(posicao == -1) {
    return;
  }

  int tamanhoLista = getTamanhoListaIndice(removidos->lista);
  const int byteProx = 5;
  CABECALHO *cabecalho = getCabecalhoFromBin(file);

  setStatus(cabecalho, '0');

  setNroRegArq(cabecalho, getNroRegArq(cabecalho) + 1);
  writeNroRegArqCabecalho(cabecalho, file);
  setNroRem(cabecalho, getNroRem(cabecalho) - 1);
  writeNroRegRemCabecalho(cabecalho, file);
  
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
    if(removidos->tamanhos[middle] > tamanho) {
      right = middle;
    } else {
      left = middle + 1;
    }

    middle = (left + right) / 2;
  }

  long long int byteOffset = getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, middle));

  return byteOffset;
}

long long int *getBestFitArrayRegistros(REMOVIDOS *removidos, REGISTRO **registros, int quantidade, FILE *file)
{
  int *tamanhos = malloc(sizeof(int) * quantidade);
  long long int *byteOffsets = malloc(sizeof(long long int) * quantidade);

  if(getTamanhoListaRemovidos(removidos) == 0)
  {
    CABECALHO *cabecalho = getCabecalhoFromBin(file);

    setNroRegArq(cabecalho, getNroRegArq(cabecalho) + quantidade);
    writeNroRegArqCabecalho(cabecalho, file);

    for(int i = 0; i < quantidade; i++)
    {
      byteOffsets[i] = -1;
    }

    free(tamanhos);

    return byteOffsets;
  }

  for(int i = 0; i < quantidade; i++) {
    if(get_tamanhoRegistro(registros[i]) == 0) {
      tamanhos[i] = -1;
      byteOffsets[i] = 0;
      continue;
    }
    tamanhos[i] = get_tamanhoRegistro(registros[i]);
  }

  // pegue o bestFit na ordem do maior para o menor
  for(int i = 0; i < quantidade; i++) {
    int maior = -1;
    int posicao = -1;

    for(int j = 0; j < quantidade; j++) {
      if(tamanhos[j] > maior) {
        maior = tamanhos[j];
        posicao = j;
      }
    }

    if(posicao == -1)
    {
      continue;
    }
    byteOffsets[posicao] = getBestFitAndFreeSpace(removidos, tamanhos[posicao], registros[posicao], file);
    tamanhos[posicao] = -1;
  }

  free(tamanhos);

  return byteOffsets;
}

long long int getBestFitAndFreeSpace(REMOVIDOS *removidos, int tamanho, REGISTRO *registro, FILE *file) {
  int left = 0;
  int right = getTamanhoListaIndice(removidos->lista) - 1;

  int middle = (left + right) / 2;

  while(left < right) {
    if(removidos->tamanhos[middle] == tamanho)
    {
      break;
    }
    else if(removidos->tamanhos[middle] > tamanho) {
      right = middle;
    } else {
      left = middle + 1;
    }

    middle = (left + right) / 2;
  }

  long long int byteOffset = getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, middle));

  // check the byteOffset of all the elements with the same size and get the one with the smallest byteOffset
  while(middle - 1 >= 0 && removidos->tamanhos[middle - 1] == tamanho) {
    if(removidos->tamanhos[middle] != removidos->tamanhos[middle - 1]) {
      break;
    }

    long long int byteOffsetAnterior = getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, middle - 1));
    byteOffset = byteOffsetAnterior;

    middle--;
  }

  if(middle + 1 < getTamanhoListaIndice(removidos->lista)) {
    long long int proxByteOffset = getByteOffsetRegistroIndice(getRegistroIndice(removidos->lista, middle + 1));
    set_prox(registro, proxByteOffset);
  }
  else {
    set_prox(registro, -1);
  }

  removerRegistroRemovidoEAtualizarArquivo(removidos, middle, file);

  return byteOffset;
}

void imprimirRemovidos(REMOVIDOS *removidos) {
  for(int i = 0; i < getTamanhoListaIndice(removidos->lista); i++) {
    REGISTRO_INDICE *registroIndice = getRegistroIndice(removidos->lista, i);
    printf("id: %d, byteOffset: %lld\n", getIndexRegistroIndice(registroIndice), getByteOffsetRegistroIndice(registroIndice));
    printf("  tamanho: %d\n", removidos->tamanhos[i]);
  }
}