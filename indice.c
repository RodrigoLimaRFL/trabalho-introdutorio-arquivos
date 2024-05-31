#include "indice.h"
#include "registro.h"

struct _lista
{
    int tamanho;
    int max_tamanho;
    REGISTRO_INDICE **registros; // a lista possui um vetor de endereços de registros
};

LISTA_INDICE *criarLista()
{
    LISTA_INDICE *lista = (LISTA_INDICE *)malloc(sizeof(LISTA_INDICE));
    lista->tamanho = 0;
    lista->max_tamanho = 1000;
    lista->registros = (REGISTRO_INDICE **)malloc(sizeof(REGISTRO_INDICE *) * lista->max_tamanho); // aloca espaço para 1000 endereços de registros

    return lista;
}

REGISTRO_INDICE *getRegistro(LISTA_INDICE *lista, int index)
{
    return lista->registros[index]; // retorna o registro de determinado index da lista
}

int getTamanho(LISTA_INDICE *lista)
{
    return lista->tamanho;
}

bool adicionarRegistro(LISTA_INDICE *lista, REGISTRO_INDICE *registro)
{
    if(lista->tamanho >= lista->max_tamanho) {
        lista->max_tamanho += 1000;
        lista->registros = (REGISTRO_INDICE **)realloc(lista->registros, sizeof(REGISTRO_INDICE *) * lista->max_tamanho);
        if(!lista->registros) {
            printf("Erro ao realocar memória.\n");
            return false;
        }
    }
    lista->registros[lista->tamanho] = registro; // adiciona o registro no final da lista
    (lista->tamanho)++;                          // atualiza o tamanho da lista
    return true;
}

bool adicionarRegistroOrdenado(LISTA_INDICE *lista, REGISTRO_INDICE *registro)
{
    if (lista->tamanho >= lista->max_tamanho) {
        lista->max_tamanho += 1000;
        lista->registros = (REGISTRO_INDICE **)realloc(lista->registros, sizeof(REGISTRO_INDICE *) * lista->max_tamanho);
        if (!lista->registros) {
            printf("Erro ao realocar memória.\n");
            return false;
        }
    }

    // Encontrar a posição correta para inserir o novo registro
    int pos = 0;
    while (pos < lista->tamanho && get_tamanhoRegistro(lista->registros[pos]) < get_tamanhoRegistro(registro)) {
        pos++;
    }

    // Deslocar os elementos para a direita para abrir espaço para o novo registro
    for (int i = lista->tamanho; i > pos; i--) {
        lista->registros[i] = lista->registros[i - 1];
    }

    // Inserir o novo registro na posição correta
    lista->registros[pos] = registro;
    (lista->tamanho)++;

    return true;
}

bool modificarRegistro(LISTA_INDICE *lista, int index, REGISTRO_INDICE *novoRegistro)
{
    lista->registros[index] = novoRegistro; // o registro de determinado index recebe o valor do novo registro
    return true;
}

// busca binaria em relação ao id
REGISTRO_INDICE *buscarRegistro(LISTA_INDICE *lista, int id)
{
    REGISTRO_INDICE *registro = NULL;

    int inicio = 0;
    int fim = lista->tamanho - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;

        if (getIndexRegistroIndice(lista->registros[meio]) == id)
        {
            registro = lista->registros[meio];
            break;
        }
        else if (getIndexRegistroIndice(lista->registros[meio]) < id)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    return registro; // se o registro não foi encontrado, retorna -1
}

// Função para remover um registro da lista
void removerRegistro(LISTA_INDICE *lista, int index)
{
    // desloca todos os registros depois do registro a ser removido para a esquerda
    for (int i = index; i < lista->tamanho - 1; i++)
    {
        lista->registros[i] = lista->registros[i + 1];
    }

    // libera a memória do registro e altera o tamanho da lista
    apagarRegistroIndice(lista->registros[lista->tamanho]);
    lista->tamanho--;
}

// Função que libera a memória da lista e de seus registros
bool apagarLista(LISTA_INDICE *lista)
{
    if (lista == NULL)
        return false;

    for (int i = 0; i < lista->tamanho; i++)
    {
        apagarRegistroIndice(lista->registros[i]);
    }
    free(lista->registros);

    free(lista);
}

// Função que imprime os campos de todos os registros da lista
void imprimirLista(LISTA_INDICE *lista)
{
    int impressoes = 0;
    for (int i = 0; i < lista->tamanho; i++)
    {
        if (get_removido(lista->registros[i]) == '0')
        { // se o registro não foi removido, imprime seus dados na tela
            impressoes++;

            // recebe o valor dos atributos do registro
            int id = getIndexRegistroIndice(lista->registros[i]);
            int byteOffset = getByteOffsetRegistroIndice(lista->registros[i]);

            printf("Index: %d\n", id);
            printf("Byte Offset: %d\n", byteOffset);
            
            printf("\n");
        }
    }

    if (impressoes == 0)
    {
        // printf("Registro inexistente.\n\n");
    }
}

bool carregarIndice(LISTA_INDICE *lista, char *file_name)
{
    FILE *file = fopen(file_name, "rb");
    if (!file)
    {
        printf("Erro ao abrir o arquivo.\n");
        return false;
    }

    fseek(file, 1, SEEK_SET); // pula o status

    int index = -1;
    long long int byteOffset = -1;

    while (fread(&index, sizeof(int), 1, file) == 1)
    {
        fread(&byteOffset, sizeof(long long int), 1, file);
        REGISTRO_INDICE *registro = criarRegistroIndice();
        setIndexRegistroIndice(registro, index);
        setByteOffsetRegistroIndice(registro, byteOffset);
        adicionarRegistro(lista, registro);
    }

    fclose(file);
    return true;
}