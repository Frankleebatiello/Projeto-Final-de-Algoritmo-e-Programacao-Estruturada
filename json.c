#include <stdio.h>   // Biblioteca para entrada e saída padrão
#include <stdlib.h>  // Biblioteca para funções utilitárias como malloc, free, atoi
#include <string.h>  // Biblioteca para manipulação de strings
#include <stdbool.h> // Biblioteca para usar o tipo booleano (true/false)

#define TAMANHO_MAXIMO_LINHA 1000 // Define o tamanho máximo de cada linha lida do arquivo
#define MAXIMO_LINHAS 27

void removerAspasDuplas(char *textoOriginal) // Função auxiliar para remover aspas duplas de uma string
{
    char *ponteiroOrigem = textoOriginal;
    char *ponteiroDestino = textoOriginal;

    while (*ponteiroOrigem) // Copia os caracteres, ignorando aspas duplas
    {
        if (*ponteiroOrigem != '"')
        {
            *ponteiroDestino = *ponteiroOrigem;
            ponteiroDestino++;
        }
        ponteiroOrigem++;
    }

    *ponteiroDestino = '\0'; // Finaliza a nova string
}

void removerVirgula(char *textoOriginal) // Função auxiliar para remover virgulas de uma string
{
    char *ponteiroOrigem = textoOriginal;
    char *ponteiroDestino = textoOriginal;

    while (*ponteiroOrigem) // Copia os caracteres, ignorando aspas duplas
    {
        if (*ponteiroOrigem != ',')
        {
            *ponteiroDestino = *ponteiroOrigem;
            ponteiroDestino++;
        }
        ponteiroOrigem++;
    }

    *ponteiroDestino = '\0'; // Finaliza a nova string
}

int extrairPergunta()
{
    // Declaração de variáveis para armazenar dados da pergunta
    char linhaLida[TAMANHO_MAXIMO_LINHA];
    char textoEnunciado[500] = "";
    char textoDica[500] = "";
    int valorDificuldade = 0;
    int contadorLinhas = 0;

    // Variáveis para controle de leitura das alternativas
    bool dentroAlternativa = false;
    char textoAlternativa[10];
    char textoResposta[200];
    bool respostaCorreta = false;

    FILE *arquivoJSON = fopen("perguntas.json", "r"); // Abre o arquivo JSON para leitura

    if (arquivoJSON == NULL) // Verifica se o arquivo foi aberto corretamente
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    for (int i = 0; i < 2; i++)
    {
        if (fgets(linhaLida, TAMANHO_MAXIMO_LINHA, arquivoJSON) != NULL);
        else
        {
            perror("Arquivo vazio, ou sem primeira linha!");
            fclose(arquivoJSON);
            return 1;
        }
    }

    while (contadorLinhas < MAXIMO_LINHAS && fgets(linhaLida, TAMANHO_MAXIMO_LINHA, arquivoJSON) != NULL)
    {
        if (strstr(linhaLida, "\"enunciado\"")) // Verifica se a linha contém o enunciado da pergunta
        {
            char *posicaoValor = strchr(linhaLida, ':');
            if (posicaoValor)
            {
                posicaoValor += 2; // Pula os caracteres ": "
                removerAspasDuplas(posicaoValor);
                removerVirgula(posicaoValor);
                posicaoValor[strcspn(posicaoValor, "\n")] = '\0'; // Remove quebra de linha
                strcpy(textoEnunciado, posicaoValor);
                printf("\nEnunciado da pergunta: %s\n", textoEnunciado);
            }
        }

        if (strstr(linhaLida, "\"alternativas\"")) // Verifica se estamos entrando na seção de alternativas
        {
            dentroAlternativa = true;
            continue;
        }

        if (dentroAlternativa && strstr(linhaLida, "\"alternativa\"")) // Verifica se a linha contém o identificador da alternativa (ex: "a)")
        {
            char *posicaoValor = strchr(linhaLida, ':');
            if (posicaoValor)
            {
                posicaoValor += 2;
                removerAspasDuplas(posicaoValor);

                removerVirgula(posicaoValor);
                posicaoValor[strcspn(posicaoValor, "\n")] = '\0';
                strcpy(textoAlternativa, posicaoValor);
            }
        }

        if (dentroAlternativa && strstr(linhaLida, "\"texto\"")) // Verifica se a linha contém o texto da alternativa
        {
            char *posicaoValor = strchr(linhaLida, ':');
            if (posicaoValor)
            {
                posicaoValor += 2;
                removerAspasDuplas(posicaoValor);
                removerVirgula(posicaoValor);
                posicaoValor[strcspn(posicaoValor, "\n")] = '\0';
                strcpy(textoResposta, posicaoValor);
            }
        }

        if (dentroAlternativa && strstr(linhaLida, "\"correta\"")) // Verifica se a linha indica se a alternativa é correta
        {
            respostaCorreta = strstr(linhaLida, "true") != NULL;
            printf("Alternativa %s %s %s\n", textoAlternativa, textoResposta, respostaCorreta ? "(Correta)" : "");
        }

        if (dentroAlternativa && strstr(linhaLida, "]")) // Verifica se estamos saindo da seção de alternativas
        {
            dentroAlternativa = false;
        }

        if (strstr(linhaLida, "\"dica\"")) // Verifica se a linha contém a dica da pergunta
        {
            char *posicaoValor = strchr(linhaLida, ':');
            if (posicaoValor)
            {
                posicaoValor += 2;
                removerAspasDuplas(posicaoValor);
                removerVirgula(posicaoValor);
                posicaoValor[strcspn(posicaoValor, "\n")] = '\0';
                strcpy(textoDica, posicaoValor);
                printf("Dica: %s\n", textoDica);
            }
        }

        if (strstr(linhaLida, "\"dificuldade\"")) // Verifica se a linha contém o nível de dificuldade
        {
            valorDificuldade = atoi(strchr(linhaLida, ':') + 1);
            printf("Nivel de dificuldade: %d\n", valorDificuldade);
        }

        contadorLinhas++;
    }

    fclose(arquivoJSON); // Fecha o arquivo após a leitura

    return 0;
}

void moodularizarJson()
{
    int listaPerguntas[]
}