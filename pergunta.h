#ifndef PERGUNTA_H
#define PERGUNTA_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALTERNATIVAS 4
#define TAMANHO_MAX 600

typedef struct // Alternativa
{
    char alternativa[MAX_ALTERNATIVAS];
    char texto[TAMANHO_MAX];
    bool correta;
} alt;

typedef struct // Pergunta
{
    char enunciado[TAMANHO_MAX];
    alt alternativas[MAX_ALTERNATIVAS];
    int numeroAlternativas;
    char dica[TAMANHO_MAX];
    int dificuldade;
    bool jaUsada;
} pgt;

typedef struct // Banco de Perguntas
{
    pgt *questoes;
    int quantidadePgt;
    int capacidade;
} bQ;

void inicializarBanco(bQ *banco);
void expandirBanco(bQ *banco);
int parseJson(const char *conteudoJson, bQ *banco);
pgt *extrairQuestao(bQ *banco, int indice);
pgt *extrairPgtDificuldade(bQ *banco, int nivel);
void resetarQuestoes(bQ *banco);
void exibirQuestao(pgt *q);
void liberarBanco(bQ *banco);

#endif