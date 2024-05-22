#include "interpreta-bin.h"
#include "cabecalho.h"

// Função que lê os valores do cabeçalho do arquivo binário e salva na struct cabeçalho
void lerCabecalhoFromBin(FILE *file, CABECALHO *cabecalho)
{
    char status;
    // lê o status do cabeçalho do arquivo e salva na variável status
    fread(&status, sizeof(char), 1, file);
    setStatus(cabecalho, status);

    // lê o topo do cabeçalho do arquivo e salva na variável topo
    long long int topo;
    fread(&topo, sizeof(long long int), 1, file);
    setTopo(cabecalho, topo);

    // lê o próximo byte offset do cabeçalho do arquivo e salva na variável proxyByteOffset
    long long int proxByteOffset;
    fread(&proxByteOffset, sizeof(long long int), 1, file);
    setProxByteOffset(cabecalho, proxByteOffset);

    // lê o número de registros não removidos do cabeçalho do arquivo e salva na variável nroRegArq
    int nroRegArq;
    fread(&nroRegArq, sizeof(int), 1, file);
    setNroRegArq(cabecalho, nroRegArq);

    // lê o número de registros removidos do cabeçalho do arquivo e salva na variável nroRem
    int nroRem;
    fread(&nroRem, sizeof(int), 1, file);
    setNroRem(cabecalho, nroRem);
}

// Função que lê os valores de um registro do arquivo binário e salva em um registro
void lerRegistroFromBin(FILE *file, REGISTRO *registro)
{
    char removido;
    fread(&removido, sizeof(char), 1, file); // lê o caractere "removido" de um registro do arquivo e salva na variável removido
    set_removido(registro, removido);

    int tamanhoRegistro;
    fread(&tamanhoRegistro, sizeof(int), 1, file); // lê o tamanho de um registro do arquivo e salva na variável tamanhoRegistro
    set_tamanhoRegistro(registro, tamanhoRegistro);

    long long int prox;
    fread(&prox, sizeof(long long int), 1, file); // lê a posição do próximo registro removido do arquivo e salva na variável prox
    set_prox(registro, prox);

    int id;
    fread(&id, sizeof(int), 1, file); // lê o id de um registro do arquivo e salva na variável id
    set_id(registro, id);

    int idade;
    fread(&idade, sizeof(int), 1, file); // lê a idade do jogador de um registro do arquivo e salva na variável idade
    set_idade(registro, idade);

    int tamNomeJogador;
    fread(&tamNomeJogador, sizeof(int), 1, file); // lê o tamanho do nome do jogador de um registro do arquivo e salva na variável tamNomeJogador
    set_tamNomeJogador(registro, tamNomeJogador);

    char *nomeJogador = (char *)malloc(tamNomeJogador);
    // lê cada caractere do nome do jogador de um registro no arquivo e salva na variavel nomeJogador
    for(int i = 0; i < tamNomeJogador; i++)
    {
        fread(&nomeJogador[i], sizeof(char), 1, file);
    }
    set_nomeJogador(registro, nomeJogador);

    int tamNacionalidade;
    fread(&tamNacionalidade, sizeof(int), 1, file); // lê o tamanho da string nacionalidade de um registro do arquivo e salva na variável tamNacionalidade
    set_tamNacionalidade(registro, tamNacionalidade);

    char *nacionalidade = (char *)malloc(tamNacionalidade);
    // lê cada caractere da string nacionalidade um registro no arquivo e salva na variavel nacionalidade
    for(int i = 0; i < tamNacionalidade; i++)
    {
        fread(&nacionalidade[i], sizeof(char), 1, file);
    }
    set_nacionalidade(registro, nacionalidade);

    int tamNomeClube;
    fread(&tamNomeClube, sizeof(int), 1, file); // lê o tamanho do nome do clube de um registro do arquivo e salva na variável tamNomeClube
    set_tamNomeClube(registro, tamNomeClube);

    char *nomeClube = (char *)malloc(tamNomeClube);
    // lê cada caractere do nome do clube um registro no arquivo e salva na variavel nomeClube
    for(int i = 0; i < tamNomeClube; i++)
    {
        fread(&nomeClube[i], sizeof(char), 1, file);
    }
    set_nomeClube(registro, nomeClube);
}

// Função que pega o cabeçalho do arquivo binário e salva em uma struct do tipo CABECALHO
CABECALHO *getCabecalhoFromBin(char *filePath)
{
    FILE *file = fopen(filePath, "rb");
    if (file == NULL) // verifica se ocorreu um erro ao abrir o arquivo no modo leitura
    {
        printf("Falha no processamento do arquivo.");
        return NULL;
    }

    // cria um cabeçalho e chama a função lerCabecalhoFromBin para atribuir os valores a ele
    CABECALHO *cabecalho = criarCabecalho();
    lerCabecalhoFromBin(file, cabecalho);

    fclose(file); // fecha o arquivo
    return cabecalho;
}

// Função que pega os registros do arquivo binário e salva na lista de registros
LISTA *getRegistrosFromBin(char *filePath)
{
    FILE *file = fopen(filePath, "rb"); // verifica se ocorreu um erro ao abrir o arquivo no modo leitura
    if (file == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return NULL;
    }

    int i = 0;
    LISTA *lista = criarLista();

    // cria um cabeçalho e chama a função lerCabecalhoFromBin para atribuir os valores a ele
    CABECALHO *cabecalho = criarCabecalho();
    lerCabecalhoFromBin(file, cabecalho);

    long long int byteOffset = getProxByteOffset(cabecalho);
    int numRegistros = getNroRegArq(cabecalho) + getNroRem(cabecalho); // número total de registros
    byteOffset = 25;

    if(numRegistros == 0) // verifica se o arquivo não possui registros
    {
        printf("Registro inexistente.\n\n");
        fclose(file); // fecha o arquivo
        return lista;
    }
    
    for (i = 0; i < numRegistros; i++)
    {
        fseek(file, byteOffset, SEEK_SET); // muda a posição do ponteiro do arquivo para a posição do byteOffset do registro
        REGISTRO *registro = criarRegistroNulo(); // cria um registro com os valores iniciais
        lerRegistroFromBin(file, registro); // salva os valores do registro do arquivo binário no registro criado
        byteOffset += get_tamanhoRegistro(registro); // muda o byteOffset para a posição do próximo registro
        adicionarRegistro(lista, registro); // adiciona o registro criado na lista
    }

    apagarCabecalho(cabecalho); // libera a memória do cabeçalho

    fclose(file); // fecha o arquivo
    return lista;
}