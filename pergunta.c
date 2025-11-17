#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include "pergunta.h"
#include "json.h"

int escolherNaoUsada(bQ *banco)
{
    if (banco->quantidadePgt == 0)
    {
        return -1;
    }

    int tentativas = 0;
    int indice;

    do
    {
        indice = rand() % banco->quantidadePgt;
        tentativas++;
    } while (banco->questoes[indice].jaUsada && tentativas < banco->quantidadePgt * 2);

    if (banco->questoes[indice].jaUsada)
    {
        return -1;
    }

    banco->questoes[indice].jaUsada = true;

    return indice;
}

void inicializarNiveis(bQ *banco)
{
    banco->nivelAtual = 1;

    for (int i = 0; i < 5; i++)
    {
        banco->niveisRestantes[i] = 0;
    }
    
    for (int i = 0; i < banco->quantidadePgt; i++)
    {
        int nivel = banco->questoes[i].dificuldade;
        if (nivel >= 1 && nivel <= 5)
        {
            banco->niveisRestantes[nivel - 1]++;
        }
    }
    
    printf("Sistema de niveis inicializado: \n");
    for (int i = 0; i < 5; i++)
    {
        if (banco->niveisRestantes[i] > 0)
        {
            printf("   Nivel %d: %d perguntas\n", i + 1, banco->niveisRestantes[i]);
        }
    }
    printf("Pressione ENTER para continuar...");
    getchar();
}

bQ carregarBancoDePerguntas(const char *caminhoArquivo)
{
    bQ banco = {0};
    banco.capacidade = 10;
    banco.questoes = malloc(sizeof(pgt) * banco.capacidade);

    printf("[DEBUG] Tentando carregar arquivo: %s\n", caminhoArquivo);

    char *json = lerArquivoJson(caminhoArquivo);
    if (!json)
    {
        fprintf(stderr, "ERRO: Arquivo de perguntas '%s' nao encontrado ou esta vazio!\n", caminhoArquivo);
        return banco;
    }

    printf("[DEBUG] Arquivo carregado com sucesso. Tamanho: %lu bytes\n", strlen(json));

    char *posicao = strstr(json, "Perguntas");
    if (!posicao)
    {
        fprintf(stderr, "[DEBUG] Nao encontrou 'Perguntas' no JSON\n");
        free(json);
        return banco;
    }
    
    posicao = strchr(posicao, '[');
    if (!posicao)
    {
        fprintf(stderr, "[DEBUG] Nao encontrou '[' apos 'Perguntas'\n");
        free(json);
        return banco;
    }

    printf("[DEBUG] Iniciando parsing das perguntas...\n");

    bool inString = false;
    bool escape = false;
    int nivelArray = 0;
    int nivelObjeto = 0;
    char *inicioObjeto = NULL;

    for (; *posicao; posicao++)
    {
        char c = *posicao;

        if (escape)
        {
            escape = false;
            continue;
        }

        if (c == '\\')
        {
            escape = true;
            continue;
        }
        if (c == '[')
        {
            nivelArray++;
            continue;
        }
        if (c == ']')
        {
            nivelArray--;
            if (nivelArray == 0)
            {
                break;
            }
            continue;
        }

        if (nivelArray == 1)
        {
            if (c == '{')
            {
                if (nivelObjeto == 0)
                {
                    inicioObjeto = posicao;
                }
                nivelObjeto++;
            }
            else if (c == '}')
            {
                nivelObjeto--;
                if (nivelObjeto == 0 && inicioObjeto)
                {
                    int tamanho = posicao - inicioObjeto + 1;
                    char *bloco = malloc(tamanho + 1);
                    strncpy(bloco, inicioObjeto, tamanho);
                    bloco[tamanho] = '\0';

                    pgt pergunta = {0};
                    pergunta.numeroAlternativas = 0;
                    pergunta.jaUsada = false;

                    char *aux = strstr(bloco, "enunciado");
                    if (aux)
                    {
                        aux = strchr(aux, ':');
                        if (aux)
                        {
                            aux++;
                            while (*aux && (*aux == ' ' || *aux == '\t'))
                                aux++;
                            int i = 0;
                            while (*aux && *aux != ',' && *aux != '}' && i < TAMANHO_MAX - 1)
                            {
                                pergunta.enunciado[i++] = *aux++;
                            }
                            pergunta.enunciado[i] = '\0';
                            while (i > 0 && pergunta.enunciado[i-1] == ' ')
                            {
                                pergunta.enunciado[--i] = '\0';
                            }
                        }
                    }

                    aux = strstr(bloco, "dica");
                    if (aux)
                    {
                        aux = strchr(aux, ':');
                        if (aux)
                        {
                            aux++;
                            while (*aux && (*aux == ' ' || *aux == '\t'))
                                aux++;
                            int i = 0;
                            while (*aux && *aux != ',' && *aux != '}' && i < TAMANHO_MAX - 1)
                            {
                                pergunta.dica[i++] = *aux++;
                            }
                            pergunta.dica[i] = '\0';
                            while (i > 0 && pergunta.dica[i-1] == ' ')
                            {
                                pergunta.dica[--i] = '\0';
                            }
                        }
                    }

                    aux = strstr(bloco, "dificuldade");
                    if (aux)
                    {
                        aux = strchr(aux, ':');
                        if (aux)
                        {
                            pergunta.dificuldade = atoi(aux + 1);
                        }
                    }

                    char *altPtr = bloco;
                    while ((altPtr = strstr(altPtr, "\"alternativa\"")) != NULL &&
                           pergunta.numeroAlternativas < MAX_ALTERNATIVAS)
                    {
                        alt *altAtual = &pergunta.alternativas[pergunta.numeroAlternativas];

                        char *t = strchr(altPtr, ':');
                        if (t)
                        {
                            t++;
                            while (*t && (*t == ' ' || *t == '\t' || *t == '\n' || *t == '\r'))
                                t++;
                            if (*t == '"')
                                t++;
                            int i = 0;
                            while (*t && *t != '"' && i < 3)
                                altAtual->alternativa[i++] = *t++;
                            altAtual->alternativa[i] = '\0';
                        }

                        t = strstr(altPtr, "\"texto\"");
                        if (t)
                        {
                            t = strchr(t, ':');
                            if (t)
                            {
                                t++;
                                while (*t && (*t == ' ' || *t == '\t' || *t == '\n' || *t == '\r'))
                                    t++;
                                if (*t == '"')
                                    t++;
                                int i = 0;
                                while (*t && *t != '"' && i < TAMANHO_MAX - 1)
                                    altAtual->texto[i++] = *t++;
                                altAtual->texto[i] = '\0';
                            }
                        }

                        t = strstr(altPtr, "correta");
                        altAtual->correta = (t && strstr(t, "true")) ? true : false;

                        pergunta.numeroAlternativas++;
                        altPtr++;
                    }

                    if (banco.quantidadePgt >= banco.capacidade)
                    {
                        banco.capacidade *= 2;
                        banco.questoes = realloc(banco.questoes, banco.capacidade * sizeof(pgt));
                    }

                    banco.questoes[banco.quantidadePgt++] = pergunta;
                    free(bloco);
                }
            }
        }
    }

    printf("[DEBUG] Total de perguntas carregadas: %d\n", banco.quantidadePgt);
    free(json);
    
    if (banco.quantidadePgt > 0)
    {
        inicializarNiveis(&banco);
    }
    
    return banco;
}

pgt obterPerguntaDificuldade(bQ *banco, int nivel)
{
    pgt perguntaVazia = {0};

    int indices[1000];
    int totalIndices = 0;

    for (int i = 0; i < banco->quantidadePgt; i++)
    {
        if (banco->questoes[i].dificuldade == nivel && !banco->questoes[i].jaUsada)
        {
            indices[totalIndices++] = i;
        }
    }
    
    if (totalIndices == 0)
    {
        printf("Nunhuma pergunta disponível para dificuldade %d!\n", nivel);
        return perguntaVazia;
    }
    
    int escolhido = indices[rand() % totalIndices];

    banco->questoes[escolhido].jaUsada = true;
    if (nivel >= 1 && nivel <= 5)
    {
        banco->niveisRestantes[nivel - 1]--;
    }
    
    return banco->questoes[escolhido];
}

pgt obterProxima(bQ *banco)
{
    pgt perguntaVazia = {0};

    while (banco->nivelAtual <= 5)
    {
        if (banco->niveisRestantes[banco->nivelAtual - 1] > 0)
        {
            printf("\n=== NIVEL %d ===\n", banco->nivelAtual);
            printf("Perguntas restantes no nivel %d: %d\n\n", banco->nivelAtual, banco->niveisRestantes[banco->nivelAtual - 1]);

            return obterPerguntaDificuldade(banco, banco->nivelAtual);
        }
        else
        {
            printf("\n*** NIVEL %d COMPLETO! ***\n", banco->nivelAtual);
            banco->nivelAtual++;

            if (banco->nivelAtual <= 5 && banco->niveisRestantes[banco->nivelAtual - 1] > 0)
            {
                printf("Avancando para NIVEL %d...\n\n", banco->nivelAtual);
            }
        }
    }
    
    printf("\n*** PARABENS! TODOS OS NIVEIS FORAM COMPLETADOS! ***\n");
    return perguntaVazia;
}

pgt obterPerguntaNaoUsada(bQ *banco)
{
    pgt perguntaVazia = {0};
    int indice = escolherNaoUsada(banco);

    if (indice == -1)
    {
        printf("Todas as perguntas ja foram usadas!\n");
        return perguntaVazia;
    }

    return banco->questoes[indice];
}

void liberarBanco(bQ *banco)
{
    if (banco->questoes)
    {
        free(banco->questoes);
        banco->questoes = NULL;
    }
    banco->quantidadePgt = 0;
    banco->capacidade = 0;
}