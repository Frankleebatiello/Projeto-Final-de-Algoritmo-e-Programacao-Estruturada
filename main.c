#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "pergunta.h"
#include "jogo.h"
#include "json.h"
#include "interface.h"
#include "utils.h"

int main()
{
    srand(time(NULL));

    int largura = larguraTerminal();

    system("cls");

    bQ banco = carregarBancoDePerguntas("perguntas.json");
    if (banco.quantidadePgt == 0)
    {
        printf("ERRO: Nenhuma pergunta carregada!\n");
        return 1;
    }

    int opcaoMenu;
    char coment[500];
    while (1)
    {
        system("cls");
        exibirTitulo(largura);
        exibirMenu(largura);

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcaoMenu);
        limparBuffer();

        switch (opcaoMenu)
        {
        case 1:
            jogarPartida(&banco, largura);
            break;
        case 2:
            exibirRegras(largura);
            getchar();
            break;
        case 3:
            desenvolvedores(largura);
            getchar();
            break;
        case 4:
            comentario(largura, coment);
            getchar();
            break;
        case 5:
            sair(largura, coment);
            break;
        default:
            printf("Opcao invalida!\n");
            printf("Pressione ENTER para continuar...");
            getchar();
        }
    }

    liberarBanco(&banco);
    return 0;
}