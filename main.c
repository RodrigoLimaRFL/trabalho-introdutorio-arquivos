#include <stdio.h>

#include "gerencia-arquivo.h"
#include "lista.h"
#include "interpreta-bin.h"
#include "cabecalho.h"

int main(int argc, char const *argv[]) {
    switch (argc) {
        case 1:
            // Ler CSV e Escrever Binário

            CABECALHO *cabecalho = criarCabecalho();
            LISTA *lista = lerCsv("Jogador.csv");
            escreveBinario(cabecalho, lista, "bin");
            break;
        case 2:
            // Ler Binario
            break;
        case 3:
            // Busca
        default:
            break;
    }

    CABECALHO *cabecalho = criarCabecalho();
    LISTA *lista = lerCsv("Jogador.csv");
    escreveBinario(cabecalho, lista, "bin");
    // cabecalho = getCabecalhoFromBin("bin");
    // LISTA *lista2 = getRegistrosFromBin("bin");
    BuscaNacionalidadeEIdade(lista, "FRANCE", 24);
    //teste();
    return 0;
}