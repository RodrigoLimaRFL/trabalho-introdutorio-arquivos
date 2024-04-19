#ifndef CABECALHO_H

  #define CABECALHO_H

  typedef struct cabecalho CABECALHO;

  CABECALHO *criarCabecalho(void);

  char getStatus(CABECALHO cabecalho);

  int getTopo(CABECALHO cabecalho);

  int getProxByteOffset(CABECALHO cabecalho);

  int getNroRegArq(CABECALHO cabecalho);

  int getNroRem(CABECALHO cabecalho);

  int setStatus(CABECALHO cabecalho, char status);

  int setTopo(CABECALHO cabecalho, int topo);

  int setProxByteOffset(CABECALHO cabecalho, double proxByteOffset)

#endif
