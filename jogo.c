#include <stdio.h>
#include <string.h>
#include "jogo.h"
#include "utils.h"

acoesJogador inicializarAcoes (int dicasQuant, int pulosQuant, int trocasQuant, int vidasQuant)
{
    acoesJogador acoes;

    acoes.dicas = dicasQuant;
    acoes.pulos = pulosQuant;
    acoes.trocas = trocasQuant;
    acoes.vidas = vidasQuant;
    acoes.pontos = 0;
    acoes.acertos = 0;
    acoes.erros = 0;

    return acoes;
}

int pularPergunta (acoesJogador *acoes, bQ *banco, pgt **perguntaAtual)
{
    if (acoes->pulos <= 0)
    {
        printf("Voce nao tem mais pulos!");
        return 0;
    }

    if (*perguntaAtual != NULL)
    {
        (*perguntaAtual)->jaUsada = 1;
    }
    
    *perguntaAtual = obterProxima(banco);

    if (*perguntaAtual == NULL)
    {
        return 0;
    }
    
    acoes->pulos--;
    printf("Pergunta pulada com sucesso!");
    return 1;
}

int trocarPergunta (acoesJogador *acoes, bQ *banco, pgt **perguntaAtual)
{
    if (acoes->trocas <= 0)
    {
        printf("Voce nao tem mais trocas!");
        return 0;
    }
    
    if (*perguntaAtual == NULL)
    {
        printf("Nenhuma pergunta para trocar!");
        return 0;
    }
    
    int nivel = (*perguntaAtual)->dificuldade;
    (*perguntaAtual)->jaUsada = 1;

    *perguntaAtual = obterPerguntaDificuldade(banco, nivel);

    if (*perguntaAtual == NULL)
    {
        printf("Nao ha mais perguntas deste nivel!");
        return 0;
    }
    
    acoes->trocas--;
    printf("Pergunta trocada com sucesso!");
    return 1;
}

int usarDica (acoesJogador *acoes, pgt *perguntaAtual)
{
    if (acoes->dicas <= 0)
    {
        printf("Voce não tem mais dicas disponiveis!");
        return 0;
    }
    
    if (perguntaAtual == NULL || perguntaAtual->dica == NULL)
    {
        return 0;
    }
    
    printf("\nDICA: %s\n\n", perguntaAtual->dica);

    acoes->dicas--;
    return 1;
}

void exibirStatus (acoesJogador *acoes)
{
    centralizarTexto("ACOES DISPONIVEIS:");
    centralizarTexto("DICAS: ");
    printf("%d\n\n", acoes->dicas);
    centralizarTexto("PULOS: ");
    printf("%d\n\n", acoes->pulos);
    centralizarTexto("TROCAS: ");
    printf("%d\n\n", acoes->trocas);
}