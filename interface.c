#include <stdio.h>
#include "utils.h"

void exibirTitulo(int largura)
{
    printf("\n\n");
    preencher(largura, '~');
    centralizarTexto("DEV GAME QUEST", largura);
    preencher(largura, '~');
    printf("\n");
}

void exibirRegras(int largura)
{
    printf("\n");
    preencher(largura, '~');
    centralizarTexto("REGRAS DO JOGO", largura);
    preencher(largura, '~');
    printf("\n");
    alinharEsquerda("1 - Voce comeca com 1 vida\n", largura);
    alinharEsquerda("2 - Ao errar uma pergunta, voce perde 1 vida\n", largura);
    alinharEsquerda("3 - Se a vida chegar a 0, voce perde o jogo\n", largura);
    alinharEsquerda("4 - Avance de nivel respondendo corretamente\n", largura);
    alinharEsquerda("5 - Venca respondendo a ultima pergunta do nivel 5\n", largura);
    printf("\n");
    centralizarTexto("ACOES ESPECIAIS (1x cada)", largura);
    printf("\n");
    alinharEsquerda("PULAR: Passa para o proximo nivel\n", largura);
    alinharEsquerda("TROCAR: Sorteia outra pergunta do nivel atual\n", largura);
    alinharEsquerda("DICA: Mostra uma dica da pergunta\n", largura);
}

void exibirMenu(int largura)
{
    printf("\n");

    preencher(largura, '~');
    centralizarTexto("MENU DE ACOES", largura);
    preencher(largura, '~');

    centralizarTexto("Seja bem vindo ao Dev Game Quest, um jogo que vai testar seus conhecimentos sobre linguagem C. Preparado, vamos la...", largura);

    printf("\n");

    alinharEsquerda("[1] - Iniciar o Game\n", largura);
    alinharEsquerda("[2] - Conhecer os desenvolvedores\n", largura);
    alinharEsquerda("[3] - Fazer um comentario\n", largura);
    alinharEsquerda("[4] - Sair\n", largura);
    printf("\n");

    preencher(largura, '~');
}

void exibirMenu2(int largura)
{
    printf("\n");
    preencher(largura, '~');
    centralizarTexto("MENU DE ACOES", largura);
    preencher(largura, '~');
    printf("\n");
    alinharEsquerda("[A/B/C/D] - Responder\n", largura);
    alinharEsquerda("[1] - Usar Dica\n", largura);
    alinharEsquerda("[2] - Pular Pergunta\n", largura);
    alinharEsquerda("[3] - Trocar Pergunta\n", largura);
    alinharEsquerda("[4] - Ver Status\n", largura);
    alinharEsquerda("[5] - Sair do Jogo\n", largura);
    printf("\n");
    preencher(largura, '~');
}