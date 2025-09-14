#include <stdio.h>
#include "interface.h"
#include "jogo.h"
#include "json.h"
#include "pergunta.h"

int main()
{
    int totalPerguntas;
    Pergunta **perguntas= carregarPergunta("perguntas.json", &totalPerguntas);

    if (!perguntas) return 1;

    Jogo *jogo = iniciarJogo(5);

    int opcao;
    do
    {
        mostrar_menu();
        opcao = ler_opcao();
        switch (opcao)
        {
        case 1:
            // lógica para responder pergunta
            break;

        case 2:
            // lógica para ação especial
            break;

        case 3:
            mostrarEstado(jogo);
            break;

        case 4:
            exibirPergunta(perguntas[jogo->nivel_atual - 1]);
            break;

        case 5:
            puts("Saindo...");
            break;
        
        default:
            puts("Opcaao Invalida.");
            break;
        }
    } while (opcao != 5);
    
    liberarJogo(jogo);
    for (int i = 0; i < totalPerguntas; i++) liberarPergunta(perguntas[i]);
    free(perguntas);
    
    return 0;
}
