#ifndef REGISTROARVOREB_H
    #define REGISTROARVOREB_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>

    #define ORDEM_ARVORE_B 4
    
    typedef struct _registroArvoreB REGISTRO_ARVORE_B;

    REGISTRO_ARVORE_B *criarRegistroArvoreBVazio();
    bool inserirChaveRegistroArvoreB(REGISTRO_ARVORE_B *registro, int chave);
    bool removerChaveRegistroArvoreB(REGISTRO_ARVORE_B *registro, int chave);
    bool inserirDescendenteRegistroArvoreB(REGISTRO_ARVORE_B *registro, long long int descendente, int chaveDescendente);
    bool removerDescendenteRegistroArvoreB(REGISTRO_ARVORE_B *registro, long long int descendente);
    int getAlturaNoRegistroArvoreB(REGISTRO_ARVORE_B *registro);
    void setAlturaNoRegistroArvoreB(REGISTRO_ARVORE_B *registro, int altura);
    int getNroChavesRegistroArvoreB(REGISTRO_ARVORE_B *registro);
    bool apagarRegistroArvoreB(REGISTRO_ARVORE_B *registro);
#endif