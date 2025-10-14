#include <stdio.h>
#include <stdlib.h>    // Para alocação dinâmica
#include <time.h>      // Para funções de tempo
#include "pergunta.h"  // Para a struct da Pergunta
#include "jogo.h"      // Para a struct do Jogo e funções relacionadas
#include "interface.h" // Para funções de interface
#include "json.h"      // Para carregar as perguntas do json
#include "utils.h"     // Para funções utilitárias

int main()
{
    srand(time(NULL));

    int total_perguntas;
    Pergunta **perguntas = carregarPerguntas("perguntas.json", &total_perguntas);
    if (!perguntas)
    {
        printf("Erro: perguntas nao forao carregadas.\n");
        return 1;
    }

    printf("[DEBUG] Total de perguntas carregadas: %d\n", total_perguntas);
    
    // Descobrir o total de níveis
    int maior_nivel = 0;
    for (int i = 0; i < total_perguntas; i++)
    {
        if (perguntas[i]->dificuldade > maior_nivel)
        {
            maior_nivel = perguntas[i]->dificuldade;
        }
    }

    printf("[DEBUG] Distribuicao de perguntas por nivel:\n");
    for (int nivel = 1; nivel <= maior_nivel; nivel++)
    {
        int count = 0;
        for (int i = 0; i < total_perguntas; i++)
        {
            if (perguntas[i]->dificuldade == nivel)
            {
                count++;
            }
        }
        printf("[DEBUG] Nivel %d: %d perguntas\n", nivel, count);
    }

    Jogo *jogo = iniciarJogo(maior_nivel);
    printf("[DEBUG] Jogo iniciado - Nivel atual: %d, Total de niveis: %d\n", 
           jogo->nivelAtual, jogo->totalNiveis);

    Pergunta *perguntaAtual = NULL;

    int opcao;
    while (jogo->vida > 0 && jogo->nivelAtual <= jogo->totalNiveis)
    {
        mostrarMenu();
        opcao = lerOpcao();

        switch (opcao)
        {
        case 1:
        {
            printf("[DEBUG] Buscando pergunta para nivel %d\n", jogo->nivelAtual);
            
            if (jogo->usarTrocar)
            {
                printf("Trocando para uma nova pergunta...\n");
                jogo->usarTrocar = 0; // Reseta a flag após usar
            }
            
            Pergunta *p = NULL; 
            int contadorNivel = 0;

            // Contar quantas perguntas existem no nível atual
            for (int i = 0; i < total_perguntas; i++)
            {
                if (perguntas[i]->dificuldade == jogo->nivelAtual)
                {
                    contadorNivel++;
                }
            }

            printf("[DEBUG] Encontradas %d perguntas para o nivel %d\n", 
                   contadorNivel, jogo->nivelAtual);

            if (contadorNivel > 0)
            {
                int sorteada = sorteio(contadorNivel);
                int contador = 0;

                for (int i = 0; i < total_perguntas; i++)
                {
                    if (perguntas[i]->dificuldade == jogo->nivelAtual)
                    {
                        if (contador == sorteada)
                        {
                            p = perguntas[i];
                            break;
                        }
                        contador++;
                    }
                }
            }

            if (!p)
            {
                printf("Nao ha perguntas para este nivel.\n");
                break;
            }

            perguntaAtual = p;

            exibirPergunta(p);
            printf("Sua resposta (letra): ");
            char letra;
            scanf(" %c", &letra);
            limparBuffer();

            if (!letraValida(letra))
            {
                printf("Letra invalida. Tente novamente.\n");
                break;
            }

            int resposta = letraParaIndice(letra);
            if (resposta == p->resposta_correta)
            {
                printf("Resposta correta!\n");
                jogo->nivelAtual++;
                if (jogo->nivelAtual > jogo->totalNiveis)
                {
                    printf("\nParabens! Voce completou todos os niveis!\n");
                }
            }
            else
            {
                printf("Resposta incorreta.\n");
                jogo->vida--;
            }
            break;
        }

        case 2:
        {
            printf("\n--- Acoes Especiais ---\n");
            printf("a) Pular questao\n");
            printf("b) Trocar questao\n");
            printf("c) Ver dica\n");
            printf("Escolha uma acao: ");
            char acao;
            scanf(" %c", &acao);
            limparBuffer();

            if (acao == 'a' && !jogo->usarPulo)
            {
                jogo->nivelAtual++;
                jogo->usarPulo = 1;
                printf("Voce pulou para o proximo nivel.\n");
                if (jogo->nivelAtual > jogo->totalNiveis)
                {
                    printf("Voce pulou o ultimo nivel e venceu o jogo!\n");
                }
            }
            else if (acao == 'b' && !jogo->usarTrocar)
            {
                jogo->usarTrocar = 1;
                printf("A proxima pergunta sera trocada por outra do mesmo nivel.\n");
            }
            else if (acao == 'c' && !jogo->usarDica)
            {
                jogo->usarDica = 1;
                if (perguntaAtual != NULL)
                {
                    printf("Dica: %s\n", perguntaAtual->dica);
                }
                else
                {
                    printf("Nenhuma pergunta foi exibida ainda.\n");
                }
            }
            else
            {
                printf("Acao invalida ou ja usada.\n");
            }
            break;
        }

        case 3:
            mostrarEstado(jogo);
            break;

        case 4:
            if (perguntaAtual != NULL)
            {
                exibirPergunta(perguntaAtual);
            }
            else
            {
                printf("Nenhuma pergunta foi exibida ainda.\n");
            }
            break;

        case 5:
            printf("Saindo do jogo...\n");
            jogo->vida = 0; // força saída
            break;

        default:
            printf("Opcao invalida.\n");
        }
    }

    if (jogo->vida == 0)
    {
        printf("\nVoce perdeu o jogo. Game Over!\n");
    }
    else if (jogo->nivelAtual > jogo->totalNiveis)
    {
        printf("\nParabens! Voce venceu o jogo completando todos os niveis!\n");
    }

    liberarJogo(jogo);
    for (int i = 0; i < total_perguntas; i++)
    {
        liberarPergunta(perguntas[i]);
    }
    free(perguntas);

    return 0;
}
