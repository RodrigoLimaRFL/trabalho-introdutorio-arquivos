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

// Função que realiza a busca do registro que possui o id passado como parâmetro na lista
REGISTRO **buscaPorId(LISTA *lista, int id)
{
  REGISTRO **registros = (REGISTRO **)malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    if (get_id(lista->registros[i]) == id && get_removido(lista->registros[i]) == '0')
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

// Função que realiza a busca do registro que possui o nome do jogador passado como parâmetro na lista
REGISTRO **buscaPorNome(LISTA *lista, char *nome)
{
  REGISTRO **registros = (REGISTRO **)malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    if (strcmp(get_nomeJogador(lista->registros[i]), nome) == 0 && get_removido(lista->registros[i]) == '0') // se o nome do jogador no registro é igual ao parâmetro nome da função e o registro não foi removido, adiciona o registro no vetor que será retornado
    {
      registros = (REGISTRO **)realloc(registros, sizeof(REGISTRO *) * (quantidade + 1));
      registros[quantidade] = lista->registros[i];
      quantidade++;
    }
  }
  // adiciona mais um registro com valor nulo no vetor para indicar o fim da lista
  registros = (REGISTRO **)realloc(registros, sizeof(REGISTRO *) * (quantidade + 1));
  registros[quantidade] = NULL;
  return registros;
}

// Função que realiza a busca do registro que possui a idade passada como parâmetro na lista
REGISTRO **buscaPorIdade(LISTA *lista, int idade)
{
  REGISTRO **registros = (REGISTRO **)malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    if (get_idade(lista->registros[i]) == idade && get_removido(lista->registros[i]) == '0') // se a idade do jogador no registro é igual ao parâmetro idade da função e o registro não foi removido, adiciona o registro no vetor que será retornado
    {
      registros = (REGISTRO **)realloc(registros, sizeof(REGISTRO *) * (quantidade + 1));
      registros[quantidade] = lista->registros[i];
      quantidade++;
    }
  }
  // adiciona mais um registro com valor nulo no vetor para indicar o fim da lista
  registros = (REGISTRO **)realloc(registros, sizeof(REGISTRO *) * (quantidade + 1));
  registros[quantidade] = NULL;
  return registros;
}

// Função que realiza a busca do registro que possui o nome do clube passado como parâmetro na lista
REGISTRO **buscaPorClube(LISTA *lista, char *clube)
{
  REGISTRO **registros = (REGISTRO **)malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    if (strcmp(get_nomeClube(lista->registros[i]), clube) == 0 && get_removido(lista->registros[i]) == '0') // se o nome do clube no registro é igual ao parâmetro clube da função e o registro não foi removido, adiciona o registro no vetor que será retornado
    {
      registros = (REGISTRO **)realloc(registros, sizeof(REGISTRO *) * (quantidade + 1));
      registros[quantidade] = lista->registros[i];
      quantidade++;
    }
  }
  // adiciona mais um registro com valor nulo no vetor para indicar o fim da lista
  registros = (REGISTRO **)realloc(registros, sizeof(REGISTRO *) * (quantidade + 1));
  registros[quantidade] = NULL;
  return registros;
}

// Função que realiza a busca do registro que possui a nacionalidade passada como parâmetro na lista
REGISTRO **buscaPorNacionalidade(LISTA *lista, char *nacionalidade)
{
  REGISTRO **registros = (REGISTRO **)malloc(0);
  int quantidade = 0;
  for (int i = 0; i < lista->tamanho; i++)
  {
    if (strcmp(get_nacionalidade(lista->registros[i]), nacionalidade) == 0 && get_removido(lista->registros[i]) == '0') // se a nacionalidade do jogador no registro é igual ao parâmetro nacionalidade da função e o registro não foi removido, adiciona o registro no vetor que será retornado
    {
      registros = (REGISTRO **)realloc(registros, sizeof(REGISTRO *) * (quantidade + 1));
      registros[quantidade] = lista->registros[i];
      quantidade++;
    }
  }
  // adiciona mais um registro com valor nulo no vetor para indicar o fim da lista
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

// Função que define o valor do campo prox em todos os registros da lista
void setProxRegistros(LISTA *lista, int index) {
  int ultimoRemovido = 0;
  long prox = 25;

  for(int i = 0; i < lista->tamanho; i++) {
    // se o registro foi removido, modifica o valor de próximo aos registros anteriores a ele e posteriores ao último removido
    if(get_removido(lista->registros[i]) == '1') {
      for (int j = ultimoRemovido; j < i; j++) {
        set_prox(lista->registros[j], prox); // atribui o valor de prox ao atributo prox do registro da posicao j
        ultimoRemovido = i;
      }
    }

    // incrementa o valor de prox com o tamanho do registro da posição i
    prox += get_tamanhoRegistro(lista->registros[i]);
  }
}

// Função que imprime os campos de todos os registros da lista
void imprimirLista(LISTA *lista) {
  int impressoes = 0;
  for(int i=0; i<lista->tamanho; i++) {
    if(get_removido(lista->registros[i]) == '0') { // se o registro não foi removido, imprime seus dados na tela
      impressoes++;

      // recebe o valor dos atributos do registro
      char *nomeClube = get_nomeClube(lista->registros[i]);
        char *nacionalidade = get_nacionalidade(lista->registros[i]);
        char *nomeJogador = get_nomeJogador(lista->registros[i]);

        printf("Nome do Jogador: ");
        if (strcmp(nomeJogador, "SEM DADO") == 0) // se o nome do jogador for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere do nome do jogador
        {
            for (int j = 0; j < get_tamNomeJogador(lista->registros[i]); j++)
            {
                printf("%c", nomeJogador[j]);
            }
            printf("\n");
        }

        printf("Nacionalidade do Jogador: ");
        if (strcmp(nacionalidade, "SEM DADO") == 0) // se a nacionalidade for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere da nacionalidade
        {
            for (int j = 0; j < get_tamNacionalidade(lista->registros[i]); j++)
            {
                printf("%c", nacionalidade[j]);
            }
            printf("\n");
        }

        printf("Clube do Jogador: ");
        if(strcmp(nomeClube, "SEM DADO") == 0) // se o nome do clube for "SEM DADO", imprime "SEM DADO"
        {
            printf("SEM DADO\n");
        }
        else // se não, imprime cada caractere do nome do clube
        {
            for(int j = 0; j<get_tamNomeClube(lista->registros[i]); j++)
            {
                printf("%c", nomeClube[j]);
            }
            printf("\n");
        }
        printf("\n");
    }
  }

  if(impressoes == 0)
  {
    printf("Registro inexistente.\n\n");
  }
}