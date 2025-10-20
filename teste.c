#include <stdio.h>
#include <string.h>

// Função para imprimir linha de traços
void linha(int largura)
{
    for (int i = 0; i < largura; i++)
        printf("-");
    printf("\n");
}

// Função para centralizar texto
void center(const char *texto, int largura)
{
    int tamanho = strlen(texto);
    int inicio = (largura - tamanho) / 2;
    if (inicio < 0)
        inicio = 0; // evita números negativos

    for (int i = 0; i < inicio; i++)
        printf(" ");
    printf("%s\n", texto);
}

int main()
{
    int largura = 138; // mesma largura da linha de traços

    linha(largura); // linha decorativa
    center("Bem Vindo!!", largura);
    center("teste da centralização", largura);
    linha(largura); // linha decorativa

    return 0;
}
