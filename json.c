#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"

void limparString(char *string)
{
    char *caminho = string;
    char *destino = string;
    
    while (*caminho)
    {
        if (*caminho != '\n' && *caminho != '\r')
        {
            *destino++ = *caminho;
        }
        caminho++;
    }
    *destino = '\0';
}

char *lerArquivoJson(const char *caminho)
{
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo %s\n", caminho);
        return NULL;
    }

    if (fseek(arquivo, 0, SEEK_END) != 0)
    {
        perror("Erro ao mover o ponteiro do arquivo!");
        fclose(arquivo);
        return NULL;
    }

    long tamanho = ftell(arquivo);
    if (tamanho <= 0) {
        fprintf(stderr, "Arquivo JSON vazio ou inválido: %s\n", caminho);
        fclose(arquivo);
        return NULL;
    }
    if (tamanho > 10 * 1024 * 1024) {
        fprintf(stderr, "Arquivo JSON muito grande (>10MB): %s\n", caminho);
        fclose(arquivo);
        return NULL;
    }

    if (fseek(arquivo, 0, SEEK_SET) != 0)
    {
        perror("Erro ao mover o ponteiro do arquivo!");
        fclose(arquivo);
        return NULL;
    }

    char *conteudo = malloc(tamanho + 1);
    if (!conteudo)
    {
        fclose(arquivo);
        return NULL;
    }

    fread(conteudo, 1, tamanho, arquivo);
    conteudo[tamanho] = '\0';
    fclose(arquivo);

    limparString(conteudo);
    return conteudo;
}