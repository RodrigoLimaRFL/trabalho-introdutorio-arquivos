#ifndef CABECALHO_H

  #define CABECALHO_H

  #include "lista.h"

  typedef struct cabecalho_ CABECALHO;

  CABECALHO *criarCabecalho(void);

  int setValoresCabecalho(CABECALHO *cabecalho, LISTA *lista);

  char getStatus(CABECALHO *cabecalho);

  int getTopo(CABECALHO *cabecalho);

  int getProxByteOffset(CABECALHO *cabecalho);

  int getNroRegArq(CABECALHO *cabecalho);

  int getNroRem(CABECALHO *cabecalho);

  void setStatus(CABECALHO *cabecalho, char status);

  void setTopo(CABECALHO *cabecalho, int topo);

  void setProxByteOffset(CABECALHO *cabecalho, double proxByteOffset);

  void setNroRegArq(CABECALHO *cabecalho, int nroRegArq);

  void setNroRem(CABECALHO *cabecalho, int nroRem);

  void apagarCabecalho(CABECALHO *cabecalho);

#endif