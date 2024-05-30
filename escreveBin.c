#include "escreveBin.h"
#include "cabecalho.h"

// Função que lê os valores do cabeçalho do arquivo binário e salva na struct cabeçalho
void lerCabecalhoFromBin2(FILE *file, CABECALHO *cabecalho)
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
void lerRegistroFromBin2(FILE *file, REGISTRO *registro)
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
CABECALHO *getCabecalhoFromBin2(char *filePath)
{
    FILE *file = fopen(filePath, "rb");
    if (file == NULL) // verifica se ocorreu um erro ao abrir o arquivo no modo leitura
    {
        printf("Falha no processamento do arquivo.");
        return NULL;
    }

    // cria um cabeçalho e chama a função lerCabecalhoFromBin para atribuir os valores a ele
    CABECALHO *cabecalho = criarCabecalho();
    lerCabecalhoFromBin2(file, cabecalho);

    fclose(file); // fecha o arquivo
    return cabecalho;
}

// Função que pega os registros do arquivo binário e salva na lista de registros
void imprimeRegistrosFromBin(char *filePath)
{
    FILE *file = fopen(filePath, "rb"); // verifica se ocorreu um erro ao abrir o arquivo no modo leitura
    if (file == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return;
    }

    int i = 0;

    // cria um cabeçalho e chama a função lerCabecalhoFromBin para atribuir os valores a ele
    CABECALHO *cabecalho = criarCabecalho();
    lerCabecalhoFromBin2(file, cabecalho);

    if (getStatus(cabecalho) == '0')
    {
        printf("Falha no processamento do arquivo.");
        fclose(file); // fecha o arquivo
        return;
    }

    long long int byteOffset = getProxByteOffset(cabecalho);
    int numRegistros = getNroRegArq(cabecalho) + getNroRem(cabecalho); // número total de registros
    byteOffset = 25;

    if(numRegistros == 0) // verifica se o arquivo não possui registros
    {
        printf("Registro inexistente.\n\n");
        fclose(file); // fecha o arquivo
        return;
    }
    
    for (i = 0; i < numRegistros; i++)
    {
        fseek(file, byteOffset, SEEK_SET); // muda a posição do ponteiro do arquivo para a posição do byteOffset do registro
        REGISTRO *registro = criarRegistroNulo(); // cria um registro com os valores iniciais
        lerRegistroFromBin2(file, registro); // salva os valores do registro do arquivo binário no registro criado
        byteOffset += get_tamanhoRegistro(registro); // muda o byteOffset para a posição do próximo registro
        imprimeRegistro(registro);
    }

    apagarCabecalho(cabecalho); // libera a memória do cabeçalho

    fclose(file); // fecha o arquivo
    return;
}

void imprimeRegistro(REGISTRO *registro) {
  if(get_removido(registro) == '0') { // se o registro não foi removido, imprime seus dados na tela

    // recebe o valor dos atributos do registro
    char *nomeClube = get_nomeClube(registro);
    char *nacionalidade = get_nacionalidade(registro);
    char *nomeJogador = get_nomeJogador(registro);

    printf("Nome do Jogador: ");
    if (strcmp(nomeJogador, "SEM DADO") == 0) // se o nome do jogador for "SEM DADO", imprime "SEM DADO"
    {
        printf("SEM DADO\n");
    }
    else // se não, imprime cada caractere do nome do jogador
    {
        for (int j = 0; j < get_tamNomeJogador(registro); j++)
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
        for (int j = 0; j < get_tamNacionalidade(registro); j++)
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
        for(int j = 0; j<get_tamNomeClube(registro); j++)
        {
            printf("%c", nomeClube[j]);
        }
        printf("\n");
    }
    printf("\n");
  }
}