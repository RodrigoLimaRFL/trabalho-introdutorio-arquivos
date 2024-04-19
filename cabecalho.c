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

int setStatus(CABECALHO *cabecalho, char status) {
  cabecalho->status = status;
}

int setTopo(CABECALHO *cabecalho, int topo) {
  cabecalho->topo = topo;
}

int setProxByteOffset(CABECALHO *cabecalho, double proxByteOffset) {
  cabecalho->proxByteOffset = proxByteOffset;
}

int setNroRegArq(CABECALHO *cabecalho, int nroRegArq) {
  cabecalho->nroRegArq = nroRegArq;
}

int setNroRem(CABECALHO *cabecalho, int nroRem) {
  cabecalho->nroRegRem = nroRem;
}

int apagarCabecalho(CABECALHO *cabecalho) {
  free(cabecalho);
}