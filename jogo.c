#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

Jogo *iniciarJogo(int totalNiveis)
{
    Jogo *j = malloc(sizeof(Jogo));
    if (!j)
    {
        return NULL;
    }
    j->nivelAtual = 1;
    j->totalNiveis = (totalNiveis > 0) ? totalNiveis : 1;
    j->vida = 3;
    j->usarPulo = j->usarTrocar = j->usarDica = 0;
    return j;
}

void mostrarEstado(Jogo *j)
{
    printf("\n--- Estado do Jogo ---\n");
    printf("Vida: %d\n", j->vida);
    printf("Nivel atual: %d de %d\n", j->nivelAtual, j->totalNiveis);
    printf("Acao Pular: %s\n", j->usarPulo ? "Usada" : "Disponivel");
    printf("Acao Trocar: %s\n", j->usarTrocar ? "Usada" : "Disponivel");
    printf("Acao Dica: %s\n", j->usarDica ? "Usada" : "Disponivel");
}

void liberarJogo(Jogo *j)
{
    free(j);
}
