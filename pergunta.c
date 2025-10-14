#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pergunta.h"

Pergunta *criarPergunta()
{
    Pergunta *p = malloc(sizeof(Pergunta));
    p->enunciado = NULL;
    p->alternativas = NULL;
    p->resposta_correta = -1;
    p->dica = NULL;
    p->dificuldade = 0;
    p->numeroAlternativas = 0;
    return p;
}

void exibirPergunta(Pergunta *p)
{
    printf("\n=== PERGUNTA (Nivel %d) ===\n", p->dificuldade);
    printf("%s\n", p->enunciado);
    printf("\nAlternativas:\n");
    for (int i = 0; i < p->numeroAlternativas; i++)
    {
        printf("  %c) %s\n", 'a' + i, p->alternativas[i]);
    }
    printf("========================\n");
}

void liberarPergunta(Pergunta *p)
{
    if (p->enunciado) free(p->enunciado);
    if (p->dica) free(p->dica);
    if (p->alternativas) {
        for (int i = 0; i < p->numeroAlternativas; i++)
        {
            if (p->alternativas[i]) free(p->alternativas[i]);
        }
        free(p->alternativas);
    }
    free(p);
}
