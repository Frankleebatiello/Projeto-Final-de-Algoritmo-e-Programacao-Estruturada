#ifndef PERGUNTA_H
#define PERGUNTA_H

#include <stdbool.h>

#define MAX_ALTERNATIVAS 4
#define TAMANHO_MAX 600

// Alternativa
typedef struct
{
    char alternativa[MAX_ALTERNATIVAS];
    char texto[TAMANHO_MAX];
    bool correta;
} alt;

// Pergunta
typedef struct
{
    char enunciado[TAMANHO_MAX];
    alt alternativas[MAX_ALTERNATIVAS];
    int numeroAlternativas;
    char dica[TAMANHO_MAX];
    int dificuldade;
    bool jaUsada;
} pgt;

// Banco de Perguntas
typedef struct
{
    pgt *questoes;
    int quantidadePgt;
    int capacidade;
    int nivelAtual;
    int niveisRestantes[5];
} bQ;

int escolherNaoUsada(bQ *banco);
bQ carregarBancoDePerguntas(const char *caminhoArquivo);
pgt obterPerguntaNaoUsada(bQ *banco);
pgt obterPerguntaDificuldade(bQ *banco, int nivel);
pgt obterProxima(bQ *banco);
void inicializarNiveis(bQ *banco);
void liberarBanco(bQ *banco);

#endif