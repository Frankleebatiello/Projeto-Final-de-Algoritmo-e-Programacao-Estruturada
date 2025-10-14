#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

int sorteio(int max) {
    if (max <= 0) return 0;
    return rand() % max;
}

int letraParaIndice(char letra) {
    return tolower(letra) - 'a';
}

int letraValida(char letra) {
    letra = tolower(letra);
    return letra >= 'a' && letra <= 'z';
}
