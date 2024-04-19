#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int escreveBinario(LISTA *lista, char *binario) {
  FILE *f = fopen(binario, "rb");

  

  for(int i=0; i<getTamanho(lista); i++) {
    fwrite(get_removido(getRegistro(lista, i)), 1, 1, f);
    fwrite(get_tamanhoRegistro(getRegistro(lista, i)), 4, 1, f);
    fwrite(get_prox(getRegistro(lista, i)), 8, 1, f);
    fwrite(get_id(getRegistro(lista, i)), 4, 1, f);
    fwrite(get_idade(getRegistro(lista, i)), 4, 1, f);
    fwrite(get_tamNomeJogador(getRegistro(lista, i)), 4, 1, f);
    fwrite(get_nomeJogador(getRegistro(lista, i)), 1, get_tamNomeJogador(getRegistro(lista, i)), f);
    fwrite(get_tamNacionalidade(getRegistro(lista, i)), 4, 1, f);
    fwrite(get_nacionalidade(getRegistro(lista, i)), 1, get_tamNacionalidade(getRegistro(lista, i)), f);
    fwrite(get_tamNomeClube(getRegistro(lista, i)), 4, 1, f);
    fwrite(get_nomeClube(getRegistro(lista, i)), 1, get_tamNomeClube(getRegistro(lista, i)), f);
  }
}