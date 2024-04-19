#ifndef LISTA_H

  #define LISTA_H

  #include "registro.h"

  typedef struct lista_ LISTA;

  LISTA *criarLista(void);

  int adicionarRegistro(LISTA *lista, REGISTRO *registro);

  int modificarRegistro(LISTA *lista, int index);

  int buscarRegistro(LISTA *lista, int id); // retorna o index do registro na lista

  int removerRegistro(LISTA *lista, int index);

  int apagarLista(LISTA *lista);

#endif
