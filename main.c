#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pergunta.h"

int main()
{
    srand(time(NULL));
    
    // Carrega o banco de perguntas
    bQ banco = carregarBancoDePerguntas("perguntas.json");
    
    if (banco.quantidadePgt == 0)
    {
        printf("Erro ao carregar perguntas!\n");
        return -1;
    }
    
    printf("\n========================================\n");
    printf("   QUIZ DE PROGRAMACAO EM C\n");
    printf("========================================\n\n");
    
    // Loop principal do quiz usando progressão por níveis
    int pontuacao = 0;
    int totalPerguntas = 0;
    
    while (1)
    {
        // Obtém próxima pergunta seguindo a progressão de níveis
        pgt pergunta = obterProxima(&banco);
        
        // Se não há mais perguntas, encerra
        if (pergunta.numeroAlternativas == 0)
        {
            break;
        }
        
        totalPerguntas++;
        
        // Exibe a pergunta
        printf("Pergunta %d:\n%s\n\n", totalPerguntas, pergunta.enunciado);
        
        // Exibe as alternativas
        for (int i = 0; i < pergunta.numeroAlternativas; i++)
        {
            printf("%s %s\n", 
                   pergunta.alternativas[i].alternativa,
                   pergunta.alternativas[i].texto);
        }
        
        // Lê a resposta do usuário
        printf("\nSua resposta (ou 'd/D' para dica): ");
        char resposta[10];
        scanf("%s", resposta);
        
        // Verifica se pediu dica
        if (resposta[0] == 'd' || resposta[0] == 'D')
        {
            printf("\nDica: %s\n\n", pergunta.dica);
            printf("Sua resposta: ");
            scanf("%s", resposta);
        }
        
        // Verifica a resposta
        bool acertou = false;
        for (int i = 0; i < pergunta.numeroAlternativas; i++)
        {
            if (pergunta.alternativas[i].alternativa[0] == resposta[0] &&
                pergunta.alternativas[i].correta)
            {
                acertou = true;
                break;
            }
        }
        
        if (acertou)
        {
            printf("\nCORRETO!\n\n");
            pontuacao++;
        }
        else
        {
            printf("\nINCORRETO!\n");
            // Mostra a resposta correta
            for (int i = 0; i < pergunta.numeroAlternativas; i++)
            {
                if (pergunta.alternativas[i].correta)
                {
                    printf("Resposta correta: %s %s\n\n",
                           pergunta.alternativas[i].alternativa,
                           pergunta.alternativas[i].texto);
                    break;
                }
            }
        }
        
        printf("----------------------------------------\n\n");
    }
    
    // Exibe resultado final
    printf("\n========================================\n");
    printf("   RESULTADO FINAL\n");
    printf("========================================\n");
    printf("Pontuacao: %d/%d (%.1f%%)\n", 
           pontuacao, totalPerguntas, 
           (float)pontuacao / totalPerguntas * 100);
    printf("========================================\n\n");
    
    // Libera memória
    liberarBanco(&banco);
    
    return 0;
}
