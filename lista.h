#ifndef LISTA_H

  #define LISTA_H

  #include "registro.h"

  typedef struct lista_ LISTA;

  LISTA *criarLista(void);

  int adicionarRegistro(REGISTRO *registro);

  int modificarRegistro(int index);

  int buscarRegistro(int id); // retorna o index do registro na lista

  int removerRegistro(int index);

  int apagarLista(LISTA *lista);

#endif
