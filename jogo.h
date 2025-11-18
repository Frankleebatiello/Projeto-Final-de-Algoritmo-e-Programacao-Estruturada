#ifndef JOGO_H
#define JOGO_H

typedef struct {
    int vidas;
    int nivel_atual;
    int total_niveis;

    int acoes_especiais;   
} Jogo;


Jogo* iniciarJogo(int total_niveis);


void atualizarJogo(Jogo *jogo, int acertou);


void mostrarEstado(Jogo *jogo);


void liberarJogo(Jogo *jogo);

#endif
