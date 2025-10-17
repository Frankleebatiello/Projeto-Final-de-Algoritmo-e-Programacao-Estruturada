#ifndef PERGUNTA_H
#define PERGUNTA_H

#include <stdbool.h>

#define MAX_ALTERNATIVAS 4
#define MAX_PERGUNTAS 100

struct alt // Alternativa
{
    char letra[4];
    char texto[100];
    bool correta;
};

struct pgt // Pergunta
{
    char enunciado[300];
    struct alt alternativas[MAX_ALTERNATIVAS];
    char dica[200];
    int dificuldade;
};

struct bP // Banco de Perguntas
{
    struct pgt perguntas[MAX_PERGUNTAS];
    int totalPerguntas;
};

#endif