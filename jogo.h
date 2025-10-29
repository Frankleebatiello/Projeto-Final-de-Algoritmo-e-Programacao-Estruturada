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
void exibirStatus (acoesJogador *acoes, int largura);
void exibirPergunta(pgt *pergunta, int numeroPergunta, int largura);

// Lógica do game
int validarResposta(pgt *pergunta, char resposta);
void perderVida(acoesJogador *acoes, int largura);
int verificarVitoria(bQ *banco);
int verificarDerrota(acoesJogador *acoes);
void exibirResultadoFinal(acoesJogador *acoes, int venceu, int largura);

// Extras
void desenvolvedores (int largura);
void comentario (int largura);

#endif