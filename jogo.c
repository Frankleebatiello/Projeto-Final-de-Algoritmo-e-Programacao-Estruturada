#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "jogo.h"
#include "utils.h"
#include "interface.h"

acoesJogador inicializarAcoes(int dicasQuant, float moedasQuant, int pulosQuant, int trocasQuant)
{
    acoesJogador acoes;

    acoes.dicas = dicasQuant;
    acoes.moedas = moedasQuant;
    acoes.pulos = pulosQuant;
    acoes.trocas = trocasQuant;
    acoes.vidas = 1;
    acoes.acertos = 0;
    acoes.erros = 0;

    return acoes;
}

int pularPergunta(acoesJogador *acoes, bQ *banco, pgt **perguntaAtual)
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

int trocarPergunta(acoesJogador *acoes, bQ *banco, pgt **perguntaAtual)
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

int usarDica(acoesJogador *acoes, pgt *perguntaAtual)
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

void exibirStatus(acoesJogador *acoes, int largura)
{
    centralizarTexto("ACOES DISPONIVEIS", largura);
    centralizarTexto("VIDAS: ", largura);
    printf("%d\n\n", acoes->vidas);
    centralizarTexto("ACERTOS: ", largura);
    printf("%d\n\n", acoes->acertos);
    centralizarTexto("ERROS: ", largura);
    printf("%d\n\n", acoes->erros);
    centralizarTexto("DICAS: ", largura);
    printf("%d\n\n", acoes->dicas);
    centralizarTexto("PULOS: ", largura);
    printf("%d\n\n", acoes->pulos);
    centralizarTexto("TROCAS: ", largura);
    printf("%d\n\n", acoes->trocas);
}

void exibirPergunta(pgt *pergunta, int numeroPergunta, int largura)
{
    if (pergunta == NULL)
    {
        printf("ERRO: Pergunta invalida!!!\n");
        return;
    }

    printf("\n");
    char cabecalho[100];
    sprintf(cabecalho, "Pergunta: %d - Difivuldade: %d\n\n", numeroPergunta, pergunta->dificuldade);
    centralizarTexto(cabecalho, largura);

    printf("%s\n\n", pergunta->enunciado);

    for (int i = 0; i < pergunta->numeroAlternativas; i++)
    {
        printf("%s %s\n", pergunta->alternativas[i].alternativa, pergunta->alternativas[i].texto);
    }
    printf("\n");
}

int validarResposta(pgt *pergunta, acoesJogador *acoes, char resposta)
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
            if (pergunta->alternativas[i].correta)
            {
                acoes->moedas += 2.5;
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }

    return 0;
}

void perderVida(acoesJogador *acoes, int largura)
{
    acoes->vidas--;
    acoes->erros++;
    centralizarTexto("\nRESPOSTA INCORRETA!!! Voce perdeu uma vida!\n", largura);
    char lyfe[19];
    sprintf(lyfe, "Vidas Restantes: %d\n", acoes->vidas);
    centralizarTexto(lyfe, largura);
}

int verificarVitoria(bQ *banco)
{
    return banco->nivelAtual > 5;
}

int verificarDerrota(acoesJogador *acoes)
{
    return acoes->vidas <= 0;
}

void exibirResultadoFinal(acoesJogador *acoes, int venceu, int largura)
{
    printf("\n\n");
    preencher(largura, '~');

    if (venceu)
    {
        centralizarTexto("PARABENS! VOCE VENCEU!", largura);
        preencher(largura, '~');
        printf("\n");
        centralizarTexto("Voce completou todos os niveis!", largura);
    }
    else
    {
        centralizarTexto("GAME OVER!", largura);
        preencher(largura, '~');
        printf("\n");
        centralizarTexto("Suas vidas acabaram!", largura);
    }

    printf("\n");
    centralizarTexto("ESTATISTICAS FINAIS", largura);
    printf("\n");
    printf("Total de Acertos: %d\n", acoes->acertos);
    printf("Total de Erros: %d\n", acoes->erros);

    if (acoes->acertos + acoes->erros > 0)
    {
        float taxa = (float)acoes->acertos / (acoes->acertos + acoes->erros) * 100;
        printf("Taxa de Acerto: %.1f%%\n", taxa);
    }

    printf("\n");
    centralizarTexto("Obrigado por jogar!", largura);
    printf("\n");
}

void loja(acoesJogador *acoes, int largura)
{
    char escolha;

    int vidaValor = 5;
    int dicaValor = 5;
    int trocarValor = 5;
    int pularValor = 5;

    char compra[3];

    while (1)
    {

        system("cls");
        char rings[20];
        sprintf(rings, "Moedas: %g", acoes->moedas);
        cabecalho("<- Sair[S]", rings, largura);

        printf("Vidas: %d\n", acoes->vidas);
        printf("Dicas: %d\n", acoes->dicas);
        printf("Pulos: %d\n", acoes->pulos);
        printf("Trocas: %d\n", acoes->trocas);

        printf("\n\n");

        printf("[V] +1 Vidas (%d/3)     Valor:%d\n", acoes->vidas, vidaValor);
        printf("[D] +1 Dicas (%d/3)     Valor:%d\n", acoes->dicas, dicaValor);
        printf("[P] +1 Pular (%d/3)     Valor:%d\n", acoes->pulos, pularValor);
        printf("[T] +1 Trocar (%d/3)    Valor:%d\n", acoes->trocas, trocarValor);

        printf("Deseja comprar: ");
        fgets(compra, sizeof(compra), stdin);
        compra[strcspn(compra, "\n")] = '\0';

        switch (tolower(compra[0]))
        {
        case 'v':
            if (acoes->vidas < 3)
            {
                if (acoes->moedas >= vidaValor)
                {
                    acoes->moedas -= vidaValor;
                    acoes->vidas++;
                    vidaValor += 5;
                }
                else
                {
                    centralizarTexto("Valor insuficiente! Pressione ENTER para continuar...", largura);
                    getchar();
                }
            }
            else
            {
                centralizarTexto("Voce atingiu o limite de vidas! Pressione ENTER para continuar...", largura);
                getchar();
            }
            break;

        case 'd':
            if (acoes->dicas < 3)
            {
                if (acoes->moedas >= dicaValor)
                {
                    acoes->moedas -= dicaValor;
                    acoes->dicas++;
                    dicaValor += 5;
                }
                else
                {
                    centralizarTexto("Valor insuficiente! Pressione ENTER para continuar...", largura);
                    getchar();
                }
            }
            else
            {
                centralizarTexto("Voce atingiu o limite de dicas! Pressione ENTER para continuar...", largura);
                getchar();
            }
            break;

        case 'p':
            if (acoes->pulos < 3)
            {
                if (acoes->moedas >= pularValor)
                {
                    acoes->moedas -= pularValor;
                    acoes->pulos++;
                    pularValor += 5;
                }
                else
                {
                    centralizarTexto("Valor insuficiente! Pressione ENTER para continuar...", largura);
                    getchar();
                }
            }
            else
            {
                centralizarTexto("Voce atingiu o limite de pulos! Pressione ENTER para continuar...", largura);
                getchar();
            }
            break;

        case 't':
            if (acoes->trocas < 3)
            {
                if (acoes->moedas >= trocarValor)
                {
                    acoes->moedas -= trocarValor;
                    acoes->trocas++;
                    trocarValor += 5;
                }
                else
                {
                    centralizarTexto("Valor insuficiente! Pressione ENTER para continuar...", largura);
                    getchar();
                }
            }
            else
            {
                centralizarTexto("Voce atingiu o limite de trocas! Pressione ENTER para continuar...", largura);
            }
            break;

        case 's':
            return;

        default:
            centralizarTexto("Opcao invalida! Pressione ENTER para continuar...", largura);
            getchar();

            break;
        }
    }
}

void jogarPartida(bQ *banco, int largura)
{
    acoesJogador acoes = inicializarAcoes(1, 20, 1, 1);

    for (int i = 0; i < banco->quantidadePgt; i++)
    {
        banco->questoes[i].jaUsada = 0;
    }
    int numeroPergunta = 1;
    pgt *perguntaAtual = malloc(sizeof(pgt));

    if (perguntaAtual == NULL)
    {
        printf("Erro ao alocar memoria para pergunta!\n");
        return;
    }

    while (!verificarDerrota(&acoes) && !verificarVitoria(banco))
    {
        *perguntaAtual = obterProxima(banco);

        if (perguntaAtual->numeroAlternativas == 0)
        {
            break;
        }

        int perguntaRespondida = 0;

        while (!perguntaRespondida)
        {
            system("cls");
            exibirPergunta(perguntaAtual, numeroPergunta, largura);
            exibirMenu2(largura);

            printf("\nSua escolha: ");
            char escolha;
            scanf(" %c", &escolha);
            limparBuffer();

            escolha = tolower(escolha);

            switch (escolha)
            {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
                if (validarResposta(perguntaAtual, &acoes, escolha))
                {
                    acoes.acertos++;
                    centralizarTexto("\n*** RESPOSTA CORRETA! ***\n", largura);
                    printf("Pressione ENTER para continuar...");
                    getchar();
                    perguntaRespondida = 1;
                    numeroPergunta++;
                }
                else
                {
                    perderVida(&acoes, largura);
                    printf("Pressione ENTER para continuar...");
                    getchar();

                    if (verificarDerrota(&acoes))
                    {
                        perguntaRespondida = 1;
                    }
                }
                break;

            case '1':
                if (!usarDica(&acoes, perguntaAtual))
                {
                    printf("Nao foi possivel usar a dica!\n");
                }
                printf("Pressione ENTER para continuar...");
                getchar();
                break;

            case '2':
                if (pularPergunta(&acoes, banco, &perguntaAtual))
                {
                    perguntaRespondida = 1;
                    numeroPergunta++;
                }
                else
                {
                    printf("Nao foi possivel pular!\n");
                    printf("Pressione ENTER para continuar...");
                    getchar();
                }
                break;

            case '3':
                if (trocarPergunta(&acoes, banco, &perguntaAtual))
                {
                    printf("Pressione ENTER para continuar...");
                    getchar();
                }
                else
                {
                    printf("Nao foi possivel trocar!\n");
                    printf("Pressione ENTER para continuar...");
                    getchar();
                }
                break;

            case '4':
                loja(&acoes, largura);
                break;

            case '5':
                system("cls");
                exibirStatus(&acoes, largura);
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;

            case '6':
                printf("Deseja realmente sair da partida? (S/N): ");
                char confirma;
                scanf(" %c", &confirma);
                limparBuffer();
                if (tolower(confirma) == 's')
                {
                    free(perguntaAtual);
                    return;
                }
                break;

            default:
                printf("Opcao invalida!\n");
                printf("Pressione ENTER para continuar...");
                getchar();
                break;
            }
        }
    }

    system("cls");
    int venceu = verificarVitoria(banco);
    exibirResultadoFinal(&acoes, venceu, largura);
    printf("\nPressione ENTER para voltar ao menu...");
    getchar();

    free(perguntaAtual);
}