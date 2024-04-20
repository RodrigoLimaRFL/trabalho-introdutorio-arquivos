#include <stdio.h>

#include "gerencia-arquivo.h"
#include "lista.h"
#include "interpreta-bin.h"
#include "cabecalho.h"

int main() {
    CABECALHO *cabecalho = criarCabecalho();
    LISTA *lista = lerCsv("Jogador.csv");
    escreveBinario(cabecalho, lista, "bin");
    // cabecalho = getCabecalhoFromBin("bin");
    LISTA *lista2 = getRegistrosFromBin("bin");
    //teste();
    return 0;
}