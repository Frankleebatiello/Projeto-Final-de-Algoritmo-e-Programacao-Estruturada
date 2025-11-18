#ifndef JOGO_H
#define JOGO_H

typedef struct {
    int vidas;
    int nivel_atual;
    int total_niveis;

    int acoes_especiais;   // exemplo: dicas, pular pergunta etc.
} Jogo;

// inicializa o jogo
Jogo* iniciarJogo(int total_niveis);

// atualiza o estado após responder uma pergunta
void atualizarJogo(Jogo *jogo, int acertou);

// mostra o estado atual (vidas, nível, ações etc)
void mostrarEstado(Jogo *jogo);

// libera memória
void liberarJogo(Jogo *jogo);

#endif
