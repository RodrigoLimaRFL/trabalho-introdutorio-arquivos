#include "cabecalho.h"

struct cabecalho_{
  char status; // indica a conscistência de um arquivo
  long topo; // byte offset de um registro removido
  long proxByteOffset; // próximo byte offset disponível
  int nroRegArq; // número de registros não removidos
  int nroRegRem; // número de registros removidos
};

// Função que cria o cabeçalho e define os valores iniciais de seus campos
CABECALHO *criarCabecalho(void) {
  CABECALHO *cabecalho = (CABECALHO *) malloc(sizeof(CABECALHO));
  cabecalho->status = '1';
  cabecalho->topo = -1;
  cabecalho->proxByteOffset = 0;
  cabecalho->nroRegArq = 0;
  cabecalho->nroRegRem = 0;

  return cabecalho;
}

// Função que atualiza os valores dos campos do cabeçalho
void setValoresCabecalho(CABECALHO *cabecalho, LISTA *lista) {
  for(int i=0; i<getTamanho(lista); i++) {
    if(get_removido(getRegistro(lista, i)) == '0') { // se o valor não foi removido, atualiza o valor do nroRegArq do cabeçalho
      (cabecalho->nroRegArq)++;
    } else { // se o valor foi removido, atualiza o valor do nroRegRem do cabeçalho
      (cabecalho->nroRegRem)++;
    }
  }
  int i = 0;
  cabecalho->proxByteOffset = 25; // Inicia o valor do proxByteOffset com 25, que é a quantidade de bytes do cabeçalho
  // enquanto não encontrou um registro não removido, incrementa o valor do proxyByteOffset com o valor do tamanho do registro atual
  while(get_removido(getRegistro(lista, i)) == '1' && (i<getTamanho(lista))) { 
    cabecalho->proxByteOffset += get_tamanhoRegistro(getRegistro(lista, i));
    i++;
  }

  if(i>=getTamanho(lista)) { // se o valor do i não for menor que o tamanho da lista, atribui o valor 0 para o proxByteOffset
    cabecalho->proxByteOffset = 0;
  }
  i = 0;
  cabecalho->topo = 25; // Inicia o valor do proxByteOffset com 25, que é a quantidade de bytes do cabeçalho
  // enquanto não encontrou um registro removido, incrementa o valor do proxyByteOffset com o valor do tamanho do registro atual
  while(get_removido(getRegistro(lista, i)) == '0' && (i<getTamanho(lista) - 1)) {
    cabecalho->topo += get_tamanhoRegistro(getRegistro(lista, i));
    i++;
  }

  if(i>=getTamanho(lista)) { // se o valor do i não for menor que o tamanho da lista, atribui o valor -1 para o topo
    cabecalho->topo = -1;
    
  }
}

// retorna o valor do status do cabeçalho
char getStatus(CABECALHO *cabecalho) {
  return cabecalho->status;
}

// retorna o valor do topo do cabeçalho
long getTopo(CABECALHO *cabecalho) {
  return cabecalho->topo;
}

// retorna o valor do proxByteOffset do cabeçalho
long getProxByteOffset(CABECALHO *cabecalho) {
  return cabecalho->proxByteOffset;
}

// retorna o valor do número de registros não removidos do cabeçalho
int getNroRegArq(CABECALHO *cabecalho) {
  return cabecalho->nroRegArq;
}

// retorna o valor do número de registros removidos do cabeçalho
int getNroRem(CABECALHO *cabecalho) {
  return cabecalho->nroRegRem;
}

// Funções de set para atribuir um valor aos campos do cabeçalho de acordo com os valores passados como parâmetro nas funções

void setStatus(CABECALHO *cabecalho, char status) {
  cabecalho->status = status;
}

void setTopo(CABECALHO *cabecalho, long topo) {
  cabecalho->topo = topo;
}

void setProxByteOffset(CABECALHO *cabecalho, double proxByteOffset) {
  cabecalho->proxByteOffset = proxByteOffset;
}

void setNroRegArq(CABECALHO *cabecalho, int nroRegArq) {
  cabecalho->nroRegArq = nroRegArq;
}

void setNroRem(CABECALHO *cabecalho, int nroRem) {
  cabecalho->nroRegRem = nroRem;
}

// Libera a memória do cabeçalho
void apagarCabecalho(CABECALHO *cabecalho) {
  free(cabecalho);
}