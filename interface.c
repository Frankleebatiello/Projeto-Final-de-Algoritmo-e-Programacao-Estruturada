#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

void mostrarMenu() {
    printf("\n--- MENU ---\n");
    printf("1) Responder pergunta\n");
    printf("2) Utilizar acao especial\n");
    printf("3) Mostrar estado do jogo\n");
    printf("4) Exibir pergunta novamente\n");
    printf("5) Sair do jogo\n");
}

int lerOpcao() {
    int opcao;
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    limparBuffer();
    return opcao;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
