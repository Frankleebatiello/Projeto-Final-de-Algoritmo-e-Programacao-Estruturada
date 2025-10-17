#include "utils.h"

void limparBuffer()
{
    int l;
    while ((l = getchar()) != '\n' && l != EOF);
}

void centralizarTexto(const char* texto)
{
    int largura = 168;

    int comprimento = strlen(texto);
    int espacos = (largura - comprimento) / 2;
    for (int i = 0; i < espacos; i++)
    {
        printf(" ");
    }
    printf("%s\n", texto);
    
}