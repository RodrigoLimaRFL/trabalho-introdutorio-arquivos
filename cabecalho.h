#ifndef CABECALHO_H

  #define CABECALHO_H

  typedef struct cabecalho CABECALHO;

  CABECALHO *criarCabecalho(void);

  char getStatus(CABECALHO cabecalho);

  int 

  REGISTRO *getRegistro(LISTA *lista, int index);

  int getTamanho(LISTA *lista);

  int adicionarRegistro(LISTA *lista, REGISTRO *registro);

  int modificarRegistro(LISTA *lista, int index, REGISTRO *novoRegistro);

  int buscarRegistro(LISTA *lista, int id); // retorna o index do registro na lista

  int removerRegistro(LISTA *lista, int index);

  int apagarLista(LISTA *lista);

#endif
