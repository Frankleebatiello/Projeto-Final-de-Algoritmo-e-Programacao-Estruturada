#ifndef JOGO_H
#define JOGO_H

#include "pergunta.h"

typedef struct {
    int dicas;
    int pulos;
    int trocas;
} acoesJogador;

acoesJogador inicializarAcoes (int dicas, int pulos, int trocas);

int pularPergunta (acoesJogador *acoes, bQ *banco, pgt **perguntaAtual);

int trocarPergunta (acoesJogador *acoes, bQ *banco, pgt **perguntaAtual);

int usarDica (acoesJogador *acoes, pgt *perguntaAtual);

void exibirStatus (acoesJogador *acoes);

#endif