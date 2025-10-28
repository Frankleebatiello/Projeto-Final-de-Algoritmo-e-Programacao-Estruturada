#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "jogo.h"
#include "utils.h"

acoesJogador inicializarAcoes (int dicasQuant, int pulosQuant, int trocasQuant)
{
    acoesJogador acoes;

    acoes.dicas = dicasQuant;
    acoes.pulos = pulosQuant;
    acoes.trocas = trocasQuant;
    acoes.vidas = 1;
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
    
    **perguntaAtual = obterProxima(banco);

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

    **perguntaAtual = obterPerguntaDificuldade(banco, nivel);

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
    centralizarTexto("VIDAS: ");
    printf("%d\n\n", acoes->vidas);
    centralizarTexto("ACERTOS: ");
    printf("%d\n\n", acoes->acertos);
    centralizarTexto("ERROS: ");
    printf("%d\n\n", acoes->erros);
    centralizarTexto("DICAS: ");
    printf("%d\n\n", acoes->dicas);
    centralizarTexto("PULOS: ");
    printf("%d\n\n", acoes->pulos);
    centralizarTexto("TROCAS: ");
    printf("%d\n\n", acoes->trocas);
}

void exibirPergunta(pgt *pergunta, int numeroPergunta)
{
    if(pergunta == NULL)
    {
        printf("ERRO: Pergunta invalida!!!\n");
        return;
    }

    printf("\n");
    char cabecalho[100];
    sprintf(cabecalho, "Pergunta: %d - Difivuldade: %d\n\n", numeroPergunta, pergunta->dificuldade);
    centralizarTexto(cabecalho);

    printf("%s\n\n", pergunta->enunciado);

    for (int i = 0; i < pergunta->numeroAlternativas; i++)
    {
        printf("%s) - %s\n", pergunta->alternativas[i].alternativa, pergunta->alternativas->texto);
    }
    printf("\n");
}

int validarResposta(pgt *pergunta, char resposta)
{
    if (pergunta == NULL)
    {
        return 0;
    }
    
    resposta = tolower(resposta);

    for (int i = 0; i < pergunta->numeroAlternativas; i++)
    {
        char alternativaLetra = tolower(pergunta->alternativas[i].alternativa[0]);

        if (alternativaLetra == resposta)
        {
            return pergunta->alternativas[i].correta ? 1 : 0;
        }
    }
    
    return 0;
}

void perderVida(acoesJogador *acoes)
{
    acoes->vidas--;
    acoes->erros++;
    printf("\nRESPOSTA INCORRETA!!! Voce perdeu uma vida!\n");
    printf("Vidas restantes: %d\n", acoes->vidas);
}

int verificarVitoria(bQ *banco)
{
    return banco->nivelAtual > 5;
}

int verificarDerrota(acoesJogador *acoes)
{
    return acoes->vidas <= 0;
}

void exibirResultadoFinal(acoesJogador *acoes, int venceu)
{
    printf("\n\n");
    centralizarTexto("========================================");
    
    if (venceu)
    {
        centralizarTexto("PARABENS! VOCE VENCEU!");
        centralizarTexto("========================================");
        printf("\n");
        centralizarTexto("Voce completou todos os niveis!");
    }
    else
    {
        centralizarTexto("GAME OVER!");
        centralizarTexto("========================================");
        printf("\n");
        centralizarTexto("Suas vidas acabaram!");
    }
    
    printf("\n");
    centralizarTexto("--- ESTATISTICAS FINAIS ---");
    printf("\n");
    printf("  Total de Acertos: %d\n", acoes->acertos);
    printf("  Total de Erros: %d\n", acoes->erros);
    
    if (acoes->acertos + acoes->erros > 0)
    {
        float taxa = (float)acoes->acertos / (acoes->acertos + acoes->erros) * 100;
        printf("  Taxa de Acerto: %.1f%%\n", taxa);
    }
    
    printf("\n");
    centralizarTexto("Obrigado por jogar!");
    printf("\n");
}