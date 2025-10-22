#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "json.h"

int quantidadePerguntas()
{

    char linhaLida;
    int numeroDeQuestoes = 0;
    int contadorLinhas = 0;

    FILE *arquivoJson = fopen("perguntas.json", "r");

    if (arquivoJson == NULL)
    {
        perror("Erro ao abrir o arquivo!");
        return 1;
    }

    for (int i = 0; i < 2; i++)
    {
        if (fgets(linhaLida, sizeof(linhaLida), arquivoJson) != NULL)
            ;
        else
        {
            perror("Arquivo vazio, ou sem primeira linha!");
            fclose(arquivoJson);
            return 1;
        }
    }

    while (contadorLinhas < 27 && fgets(linhaLida, sizeof(linhaLida), arquivoJson) != NULL)
    {
        while ((numeroDeQuestoes = fgetc(arquivoJson)) != EOF)
        {
            if (numeroDeQuestoes == '\n')
            {
                printf("%d", numeroDeQuestoes);
                numeroDeQuestoes++;
            }
        }
        
        contadorLinhas++;
    }
}