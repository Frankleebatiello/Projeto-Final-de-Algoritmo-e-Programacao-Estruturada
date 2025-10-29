
#include <stdlib.h>
#include <time.h>
#include "interface.h"
#include "jogo.h"
#include "json.h"
#include "pergunta.h"
#include "utils.h"

int main()
{
    srand(time(NULL));

    int largura = larguraTerminal();
    int menu1;

    do
    {
        system("cls");

        exibirTitulo(largura);
        exibirMenu(largura);

        limparBuffer();
        scanf("%d", &menu1);

        switch (menu1)
        {
        case 1:
            exibirRegras(largura);
            exibirMenu2(largura);

            char menu2;
            limparBuffer();
            scanf("%c", menu2);
            menu2 = toupper(menu2);

            switch (menu2)
            {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
                int validarResposta(pgt * pergunta, menu2) break;

            case '1':
                int usarDica(acoesJogador * acoes, pgt * perguntaAtual);
                break;

            case '2':
                int pularPergunta(acoesJogador * acoes, bQ * banco, pgt * *perguntaAtual);
                break;

            case '3':
                int trocarPergunta(acoesJogador * acoes, bQ * banco, pgt * *perguntaAtual);
                break;

            case '4':
                void exibirStatus(acoesJogador * acoes, int largura);
                break;

            case '5':
                printf("Tem certeza que deseja sair?");
                printf("[S] - Sim\n");
                printf("[N] - Nao\n");

                break;

            default:
                break;
            }
            break;
        case 2:
            desenvolvedores(largura);
            break;

        case 3:
            comentario(largura);
            break;

        case 4:
            break;

        default:
            printf("Opcao invalida! Pressione ENTER para continuar...");
            getchar();
            getchar();
            break;
        }
    } while (menu1 != 4);

    return 0;
}