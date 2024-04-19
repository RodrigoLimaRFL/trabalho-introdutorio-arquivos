#include <stdio.h>

#include "gerencia-arquivo.h"
#include "lista.h"
#include "interpreta-bin.h"

int main() {
    LISTA *lista = lerCsv("Jogador.csv");
    escreveBinario(lista, "bin");
    LISTA *lista2 = getRegistrosFromBin("bin");
    //teste();
    return 0;
}