#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

void exibirTitulo(int largura)
{
    centralizarTexto("DEV GAME QUEST", largura);
    printf("\n");
    centralizarTexto("Teste seus conhecimentos em programacao!", largura);
    printf("\n");
    preencher(largura, '_');
    printf("\n");
}

void cabecalho(const char *texto1, const char *texto2, int largura)
{
    int cabecalho = largura / 2;

    printf("%-*s", cabecalho, texto1);
    printf("%*s", cabecalho, texto2);
    printf("\n");
}

void exibirRegras(int largura)
{
    system("cls");

    preencher(largura, '_');
    printf("\n");
    centralizarTexto("REGRAS DO JOGO", largura);
    printf("\n");
    preencher(largura, '_');
    printf("\n\n");

    alinharEsquerda("1. Voce comeca com 1 vida", largura);
    alinharEsquerda("2. Cada resposta errada remove 1 vida", largura);
    alinharEsquerda("3. O jogo termina quando suas vidas chegam a zero", largura);
    alinharEsquerda("4. Voce comeca com alguns recursos especiais:", largura);
    alinharEsquerda("   - 1 Dica: revela uma pista sobre a resposta", largura);
    alinharEsquerda("   - 1 Pulo: pula a pergunta sem perder vida", largura);
    alinharEsquerda("   - 1 Troca: troca a pergunta atual por outra", largura);
    alinharEsquerda("5. Voce pode comprar mais recursos ou vidas na loja", largura);
    alinharEsquerda("6. As perguntas ficam mais dificeis conforme avanca", largura);
    alinharEsquerda("7. Venca respondendo todas as perguntas!", largura);

    printf("\n");
    preencher(largura, '_');

    printf("\nPressione ENTER para continuar...");
}

void exibirMenu(int largura)
{
    centralizarTexto("MENU DE PRINCIPAL", largura);
    printf("\n");
    printf("\n");

    alinharEsquerda("[1] - Iniciar o Game\n", largura);
    alinharEsquerda("[2] - Ver regras\n", largura);
    alinharEsquerda("[3] - Conhecer os desenvolvedores\n", largura);
    alinharEsquerda("[4] - Fazer um comentario\n", largura);
    alinharEsquerda("[5] - Sair\n", largura);

    preencher(largura, '~');
}

void exibirMenu2(int largura)
{
    preencher(largura, '-');
    centralizarTexto("ACOES", largura);
    printf("\n");
    preencher(largura, '-');
    printf("\n");

    alinharEsquerda("[A/B/C/D] - Responder", largura);
    alinharEsquerda("[1] - Usar Dica", largura);
    alinharEsquerda("[2] - Pular Pergunta", largura);
    alinharEsquerda("[3] - Trocar Pergunta", largura);
    alinharEsquerda("[4] - Loja", largura);
    alinharEsquerda("[5] - Ver Status", largura);
    alinharEsquerda("[6] - Voltar ao menu", largura);

    printf("\n");
    preencher(largura, '-');
}

int sair(int largura, const char *comentario)
{
    char entrada[2];
    char saida;

    while (1)
    {
        system("cls");

        printf("\n\n");
        alinharEsquerda("Tem certeza que deseja sair?", largura);
        alinharEsquerda("[S] - Sim\n", largura);
        alinharEsquerda("[N] - Nao\n", largura);

        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';
        saida = tolower(entrada[0]);

        if (saida == 's')
        {
            printf("Seu comentario: %s\n", comentario);
            centralizarTexto("Obrigado por participar do Game, volte quando quiser!", largura);
            printf("\n");
            exit(EXIT_SUCCESS);
        }
        else if (saida == 'n')
        {
            return 0;
        }
        else
        {
            printf("\nOpcao invalida! Pressione ENTER para continuar...");
            getchar();
            getchar();
        }
    }
}

void desenvolvedores(int largura)
{
    system("cls");

    printf("\n");
    preencher(largura, '=');
    centralizarTexto("DESENVOLVEDORES", largura);
    printf("\n");
    preencher(largura, '=');
    printf("\n");

    alinharEsquerda("Dev Game Quest v1.0", largura);
    printf("\n");

    alinharEsquerda("     - Franklee Batiello Vieira Rocha - 19 anos", largura);
    alinharEsquerda("     - Fernando de Araujo Dias - 19 anos", largura);
    alinharEsquerda("     - Miguel Guimaraes Galvao - 19 anos", largura);
    alinharEsquerda("     - Miguel Dourado de Jesus - 18 anos", largura);
    alinharEsquerda("     - Gustavo Augusto Leite - 18 anos", largura);
    alinharEsquerda("     - Lucas de Souza Martins Araujo - 19 anos", largura);

    centralizarTexto("Um jogo educativo sobre programacao", largura);
    centralizarTexto("criado para testar e expandir conhecimentos", largura);
    centralizarTexto("em diversas areas da computacao.", largura);

    printf("\n\n");
    preencher(largura, '=');

    printf("\nPressione ENTER para continuar...");
}

void comentario(int largura, char *comentario)
{
    system("cls");

    printf("\n");
    preencher(largura, '=');
    centralizarTexto("DEIXE SEU COMENTARIO", largura);
    printf("\n");
    preencher(largura, '=');
    printf("\n");

    alinharEsquerda("Digite seu comentario sobre o jogo (500 caracteres):", largura);
    printf("\n> ");

    if (fgets(comentario, sizeof(comentario), stdin) == NULL)
    {
        perror("Erro ao ler comentário");
        return;
    }

    comentario[strcspn(comentario, "\n")] = '\0';

    printf("\n");
    centralizarTexto("Obrigado pelo seu feedback!", largura);
    printf("\n");
    centralizarTexto("Seu comentario foi registrado.", largura);
    printf("\n");
    printf("Pressione ENTER para continuar...");
    limparBuffer();
    getchar();
}