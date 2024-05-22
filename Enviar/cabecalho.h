#ifndef CABECALHO_H

  #define CABECALHO_H

  #include "lista.h"

  typedef struct cabecalho_ CABECALHO;

  CABECALHO *criarCabecalho(void);

  void setValoresCabecalho(CABECALHO *cabecalho, LISTA *lista);

  char getStatus(CABECALHO *cabecalho);

  long long int getTopo(CABECALHO *cabecalho);

  long long int getProxByteOffset(CABECALHO *cabecalho);

  int getNroRegArq(CABECALHO *cabecalho);

  int getNroRem(CABECALHO *cabecalho);

  void setStatus(CABECALHO *cabecalho, char status);

  void setTopo(CABECALHO *cabecalho, long long int topo);

  void setProxByteOffset(CABECALHO *cabecalho, long long int proxByteOffset);

  void setNroRegArq(CABECALHO *cabecalho, int nroRegArq);

  void setNroRem(CABECALHO *cabecalho, int nroRem);

  void apagarCabecalho(CABECALHO *cabecalho);

#endif