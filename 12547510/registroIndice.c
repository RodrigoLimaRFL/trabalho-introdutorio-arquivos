#include "registroIndice.h"

struct _registro_indice {
    int index;
    long long int byteOffset;
};

REGISTRO_INDICE *criarRegistroIndice() {
    REGISTRO_INDICE *registro = (REGISTRO_INDICE *) malloc(sizeof(REGISTRO_INDICE));
    if(!registro)
        return NULL;
    registro->index = -1;
    registro->byteOffset = -1;
    return registro;
}

void apagarRegistroIndice(REGISTRO_INDICE *registro) {
    free(registro);
}

void setIndexRegistroIndice(REGISTRO_INDICE *registro, int index) {
    registro->index = index;
}

void setByteOffsetRegistroIndice(REGISTRO_INDICE *registro, long long int byteOffset) {
    registro->byteOffset = byteOffset;
}

int getIndexRegistroIndice(REGISTRO_INDICE *registro) {
    return registro->index;
}

long long int getByteOffsetRegistroIndice(REGISTRO_INDICE *registro) {
    return registro->byteOffset;
}