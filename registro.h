typedef struct registro REGISTRO;

#include <stdio.h>
#include <stdlib.h>

void imprimirRegistros(REGISTRO **registros);
REGISTRO **intersecaoDoisRegistros(REGISTRO **registro1, REGISTRO **registro2);
REGISTRO *criarRegistroNulo();
REGISTRO* criarRegistro(char removido, int tamanhoRegistro, long prox, int id, int idade, int tamNomeJogador, char *nomeJogador, int tamNacionalidade, char *nacionalidade, int tamNomeClube, char *nomeClube);
char get_removido(REGISTRO *registro);
int get_tamanhoRegistro(REGISTRO *registro);
long get_prox(REGISTRO *registro);
int get_id(REGISTRO *registro);
int get_idade(REGISTRO *registro);
int get_tamNomeJogador(REGISTRO *registro);
char* get_nomeJogador(REGISTRO *registro);
int get_tamNacionalidade(REGISTRO *registro);
char* get_nacionalidade(REGISTRO *registro);
int get_tamNomeClube(REGISTRO *registro);
char* get_nomeClube(REGISTRO *registro);
void set_prox(REGISTRO *registro, long prox);
void set_removido(REGISTRO *registro, int removido);
void set_tamanhoRegistro(REGISTRO *registro, int tamanhoRegistro);
void set_id(REGISTRO *registro, int id);
void set_idade(REGISTRO *registro, int idade);
void set_tamNomeJogador(REGISTRO *registro, int tamNomeJogador);
void set_nomeJogador(REGISTRO *registro, char *nomeJogador);
void set_tamNacionalidade(REGISTRO *registro, int tamNacionalidade);
void set_nacionalidade(REGISTRO *registro, char *nacionalidade);
void set_tamNomeClube(REGISTRO *registro, int tamNomeClube);
void set_nomeClube(REGISTRO *registro, char *nomeClube);
void liberarRegistro(REGISTRO *registro);
