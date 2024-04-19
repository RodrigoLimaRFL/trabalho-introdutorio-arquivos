#include "cabecalho.h"

struct cabecalho_{
  char status;
  int topo;
  double proxByteOffset;
  int nroRegArq;
  int nroRegRem;
};

CABECALHO *criarCabecalho(void);

char getStatus(CABECALHO cabecalho);

int getTopo(CABECALHO cabecalho);

int getProxByteOffset(CABECALHO cabecalho);

int getNroRegArq(CABECALHO cabecalho);

int getNroRem(CABECALHO cabecalho);

int setStatus(CABECALHO cabecalho, char status);

int setTopo(CABECALHO cabecalho, int topo);

int setProxByteOffset(CABECALHO cabecalho, double proxByteOffset);

int setNroRegArq(CABECALHO cabecalho, int nroRegArq);

int setNroRem(CABECALHO cabecalho, int nroRem);