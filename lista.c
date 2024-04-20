#include "lista.h"
#include "cabecalho.h"

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

REGISTRO **buscaPorId(LISTA *lista, int id)
{
  REGISTRO **registros = (REGISTRO **)malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    if (get_id(lista->registros[i]) == id)
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

REGISTRO **buscaPorNome(LISTA *lista, char *nome)
{
  REGISTRO **registros = (REGISTRO **)malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    if (strcmp(get_nomeJogador(lista->registros[i]), nome) == 0)
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

REGISTRO **buscaPorIdade(LISTA *lista, int idade)
{
  REGISTRO **registros = (REGISTRO **)malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    if (get_idade(lista->registros[i]) == idade)
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

REGISTRO **buscaPorClube(LISTA *lista, char *clube)
{
  REGISTRO **registros = (REGISTRO **)malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    if (strcmp(get_nomeClube(lista->registros[i]), clube) == 0)
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

REGISTRO **buscaPorNacionalidade(LISTA *lista, char *nacionalidade)
{
  REGISTRO **registros = (REGISTRO **)malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    if (strcmp(get_nacionalidade(lista->registros[i]), nacionalidade) == 0)
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

void setProxRegistros(LISTA *lista, int index) {
  int ultimoRemovido = 0;
  long prox = 25;

  for(int i = 0; i < lista->tamanho; i++) {

    if(get_removido(lista->registros[i]) == '1') {
      for (int j = ultimoRemovido; j < i; j++) {
        set_prox(lista->registros[j], prox);
        ultimoRemovido = i;
      }
    }

    prox += get_tamanhoRegistro(lista->registros[i]);
  }
}

// Função que imprime os campos de todos os registros da lista
void imprimirLista(LISTA *lista) {
  for(int i=0; i<lista->tamanho; i++) {
    if(get_removido(lista->registros[i]) == '0') {
      printf("Nome do Jogador: %s\n", get_nomeJogador(lista->registros[i]));
      printf("Nacionalidade do Jogador: %s\n", get_nacionalidade(lista->registros[i]));
      printf("Clube do Jogador: %s\n\n", get_nomeClube(lista->registros[i]));
    }
  }
}