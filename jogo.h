#ifndef JOGO_H
#define JOGO_H

typedef struct
{
    int vida;
    int nivelAtual;
    int totalNiveis;

    int usarPulo;
    int usarTrocar;
    int usarDica;
}Jogo;

Jogo *iniciarJogo(int totalNiveis);
void mostrarEstado(Jogo *j);
void liberarJogo(Jogo *j);

#endif
