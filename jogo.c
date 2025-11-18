#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

Jogo* iniciarJogo(int total_niveis)
{
    Jogo *j = malloc(sizeof(Jogo));
    if (!j) return NULL;

    j->vidas = 3;
    j->nivel_atual = 1;
    j->total_niveis = total_niveis;

    j->acoes_especiais = 1;   

    return j;
}

void atualizarJogo(Jogo *jogo, int acertou)
{
    if (acertou) {
        printf("\n✔ Resposta Certa! Voce passou de nivel.\n");
        jogo->nivel_atual++;

        if (jogo->nivel_atual > jogo->total_niveis) {
            jogo->nivel_atual = jogo->total_niveis;
            printf("\n🎉 Voce concluiu todas as perguntas!\n");
        }

    } else {
        printf("\n✘ Resposta errada! Você perdeu uma vida.\n");
        jogo->vidas--;

        if (jogo->vidas <= 0) {
            printf("\n💀 Voce perdeu todas as vidas! Fim de jogo.\n");
        }
    }
}

void mostrarEstado(Jogo *jogo)
{
    printf("\n====== ESTADO DO JOGO ======\n");
    printf("Vidas: %d\n", jogo->vidas);
    printf("Nivel atual: %d / %d\n", jogo->nivel_atual, jogo->total_niveis);
    printf("Acoes especiais restantes: %d\n", jogo->acoes_especiais);
    printf("=============================\n");
}

void liberarJogo(Jogo *jogo)
{
    free(jogo);
}
