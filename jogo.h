#ifndef JOGO_H
#define JOGO_H

#include "pergunta.h"

typedef struct {
    int dicas;
    int pulos;
    int trocas;
    int vidas;
    int acertos;
    int erros;
} acoesJogador;

// Inicialização das ações especiais
acoesJogador inicializarAcoes (int dicas, int pulos, int trocas);


// Ações especiais
int pularPergunta (acoesJogador *acoes, bQ *banco, pgt **perguntaAtual);
int trocarPergunta (acoesJogador *acoes, bQ *banco, pgt **perguntaAtual);
int usarDica (acoesJogador *acoes, pgt *perguntaAtual);

// Exibição
void exibirStatus (acoesJogador *acoes);
void exibirPergunta(pgt *pergunta, int numeroPergunta);

// Lógica do game
int validarResposta(pgt *pergunta, char resposta);
void perderVida(acoesJogador *acoes);
int verificarVitoria(bQ *banco);
int verificarDerrota(acoesJogador *acoes);
void exibirResultadoFinal(acoesJogador *acoes, int venceu);

#endif