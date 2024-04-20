#include "lista.h"

struct lista_ {
  int tamanho;
  REGISTRO **registros; // a lista possui um vetor de endereços de registros
};

LISTA *criarLista() {
  LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
  lista->tamanho = 0;
  lista->registros = (REGISTRO **) malloc(sizeof(REGISTRO *) * 1500); // aloca espaço para 1500 endereços de registros

  return lista;
}

REGISTRO *getRegistro(LISTA *lista, int index) {
  return lista->registros[index]; // retorna o registro de determinado index da lista
}

int getTamanho(LISTA *lista) {
  return lista->tamanho;
}

int adicionarRegistro(LISTA *lista, REGISTRO *registro) {
  lista->registros[lista->tamanho] = registro; // adiciona o registro no final da lista
  (lista->tamanho)++; // atualiza o tamanho da lista
  return 1;
}

int modificarRegistro(LISTA *lista, int index, REGISTRO *novoRegistro) {
  lista->registros[index] = novoRegistro; // o registro de determinado index recebe o valor do novo registro
  return 1;
}

int buscarRegistro(LISTA *lista, int id) {
  // faz uma busca linear O(n) para buscar o registro que possui um determinado id
  for(int i=0; i<lista->tamanho; i++) {
    if(get_id(lista->registros[i]) == id) {
      return i;
    }
  }
  return -1; // se o registro não foi encontrado, retorna -1
}

// Função que realiza a busca por nacionalidade e idade e retorna os registros que satisfazem as condições de busca passadas como argumentos na função 
REGISTRO **buscarPorNacionalidadeEIdadeAux(LISTA *lista, char *nacionalidade, int idade) {
  REGISTRO **registros = (REGISTRO **) malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    // se os campos nacionalidade e idade do registro for igual aos valores desejados, cria um ponteiro de registro que aponta para o registro que satisfaz a condição
    if (strcmp(get_nacionalidade(lista->registros[i]), nacionalidade) == 0 && get_idade(lista->registros[i]) == idade)
    {
      registros = (REGISTRO **)realloc(registros, sizeof(REGISTRO *) * (quantidade + 1));
      registros[quantidade] = lista->registros[i];
      quantidade++;
    }
  }
  // cria um novo ponteiro de registro e atribui o valor NULL a ele
  registros = (REGISTRO **)realloc(registros, sizeof(REGISTRO *) * (quantidade + 1));
  registros[quantidade] = NULL;
  return registros;
}

// Função que imprime os valores da busca por nacionalidade e idade
void BuscaNacionalidadeEIdade(LISTA *lista, char *nacionalidade, int idade)
{
  REGISTRO **registros = buscarPorNacionalidadeEIdadeAux(lista, nacionalidade, idade); // faz a busca por nacionalidade e idade na lista
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
  free(registros); // libera o espaço na memória dos registros
}

// Função para remover um registro da lista
int removerRegistro(LISTA *lista, int index) {
  // desloca todos os registros depois do registro a ser removido para a esquerda
  for(int i=index; i<lista->tamanho-1; i++) {
    lista->registros[i] = lista->registros[i+1];
  }

  // libera a memória do registro e altera o tamanho da lista
  free(lista->registros[lista->tamanho]);
  lista->tamanho--;
}


// Função que libera a memória da lista e de seus registros
int apagarLista(LISTA *lista) {
  for(int i=0; i<lista->tamanho; i++) {
    free(lista->registros[i]);
  }

  free(lista);
}