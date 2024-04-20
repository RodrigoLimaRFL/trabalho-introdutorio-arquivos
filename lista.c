#include "lista.h"

struct lista_ {
  int tamanho;
  REGISTRO **registros;
};

LISTA *criarLista() {
  LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
  lista->tamanho = 0;
  lista->registros = (REGISTRO **) malloc(sizeof(REGISTRO *) * 1500);

  return lista;
}

REGISTRO *getRegistro(LISTA *lista, int index) {
  return lista->registros[index];
}

int getTamanho(LISTA *lista) {
  return lista->tamanho;
}

int adicionarRegistro(LISTA *lista, REGISTRO *registro) {
  lista->registros[lista->tamanho] = registro;
  (lista->tamanho)++;
  return 1;
}

int modificarRegistro(LISTA *lista, int index, REGISTRO *novoRegistro) {
  lista->registros[index] = novoRegistro;
  return 1;
}

int buscarRegistro(LISTA *lista, int id) {
  for(int i=0; i<lista->tamanho; i++) {
    if(get_id(lista->registros[i]) == id){
      return i;
    }
  }
  return -1;
}

REGISTRO **buscarPorNacionalidadeEIdadeAux(LISTA *lista, char *nacionalidade, int idade)
{
  REGISTRO **registros = (REGISTRO **)malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    if (strcmp(get_nacionalidade(lista->registros[i]), nacionalidade) == 0 && get_idade(lista->registros[i]) == idade)
    {
      registros = (REGISTRO **)realloc(registros, sizeof(REGISTRO *) * (quantidade + 1));
      registros[quantidade] = lista->registros[i];
      quantidade++;
    }
  }
  registros = (REGISTRO **)realloc(registros, sizeof(REGISTRO *) * (quantidade + 1));
  registros[quantidade] = NULL;
  return registros;

}

void BuscaNacionalidadeEIdade(LISTA *lista, char *nacionalidade, int idade)
{
  REGISTRO **registros = buscarPorNacionalidadeEIdadeAux(lista, nacionalidade, idade);
  for (int i = 0; registros[i] != NULL; i++)
  {
    printf("Registro %d\n", i);
    printf("Id: %d\n", get_id(registros[i]));
    printf("Idade: %d\n", get_idade(registros[i]));
    printf("Nome do jogador: %s\n", get_nomeJogador(registros[i]));
    printf("Nacionalidade: %s\n", get_nacionalidade(registros[i]));
    printf("Nome do clube: %s\n", get_nomeClube(registros[i]));
    printf("\n");
  }
  free(registros);
}

int removerRegistro(LISTA *lista, int index) {
  for(int i=index; i<lista->tamanho-1; i++) {
    lista->registros[i] = lista->registros[i+1];
  }

  free(lista->registros[lista->tamanho]);
  lista->tamanho--;
}

int apagarLista(LISTA *lista) {
  for(int i=0; i<lista->tamanho; i++) {
    free(lista->registros[i]);
  }

  free(lista);
}