#include "cabecalho.h"

struct cabecalho_{
  char status;
  int topo;
  long proxByteOffset;
  int nroRegArq;
  int nroRegRem;
};

CABECALHO *criarCabecalho(void) {
  CABECALHO *cabecalho = (CABECALHO *) malloc(sizeof(CABECALHO));
  cabecalho->status = '1';
  cabecalho->topo = -1;
  cabecalho->proxByteOffset = 0;
  cabecalho->nroRegArq = 0;
  cabecalho->nroRegRem = 0;
}
int setValoresCabecalho(CABECALHO *cabecalho, LISTA *lista) {
  for(int i=0; i<getTamanho(lista); i++) {
    if(get_removido(getRegistro(lista, i)) == 0) {
      
    } else {

    }
  }
}

char getStatus(CABECALHO *cabecalho) {
  return cabecalho->status;
}

int getTopo(CABECALHO *cabecalho) {
  return cabecalho->topo;
}

long getProxByteOffset(CABECALHO *cabecalho) {
  return cabecalho->proxByteOffset;
}

int getNroRegArq(CABECALHO *cabecalho) {
  return cabecalho->nroRegArq;
}

int getNroRem(CABECALHO *cabecalho) {
  return cabecalho->nroRegRem;
}

void setStatus(CABECALHO *cabecalho, char status) {
  cabecalho->status = status;
}

void setTopo(CABECALHO *cabecalho, int topo) {
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

void apagarCabecalho(CABECALHO *cabecalho) {
  free(cabecalho);
}