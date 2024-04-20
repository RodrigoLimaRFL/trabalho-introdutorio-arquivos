#ifndef LISTA_H

  #define LISTA_H

  #include "registro.h"

  #include <string.h>

  typedef struct lista_ LISTA;

  LISTA *criarLista(void);

  REGISTRO *getRegistro(LISTA *lista, int index);

  int getTamanho(LISTA *lista);

  int adicionarRegistro(LISTA *lista, REGISTRO *registro);

  int modificarRegistro(LISTA *lista, int index, REGISTRO *novoRegistro);

  int buscarRegistro(LISTA *lista, int id); // retorna o index do registro na lista

  void BuscaNacionalidadeEIdade(LISTA *lista, char *nacionalidade, int idade);

  int removerRegistro(LISTA *lista, int index);

  int apagarLista(LISTA *lista);

#endif
