#include "criarIndice.h"

// Adicionar byteoffset
void criarArquivoDeIndice(LISTA *listaRegistros, CABECALHO *cabecalho)
{
    INDICE *indice = criarIndice();
    setStatusIndice(indice, '1');
    for(int i = 0; i < getTamanho(listaRegistros); i++)
    {
        REGISTRO *registro = getRegistro(listaRegistros, i);
        if(get_removido(registro) == '0')
        {
            REGISTRO_DADOS *registroDados = criarRegistroDados();
            setIndexRegistroIndice(registroDados, get_id(registro));
            setByteOffsetRegistroIndice(registroDados, i);
            insertRegistroIndice(indice, registroDados);
        }
    }
    setStatusIndice(indice, '0');

    printRegistrosIndice(indice);
}