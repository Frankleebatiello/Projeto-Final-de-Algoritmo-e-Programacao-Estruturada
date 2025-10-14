#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"

Pergunta **carregarPerguntas(const char *nome_arquivo, int *total_perguntas) 
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("[DEBUG] Erro ao abrir o arquivo %s\n", nome_arquivo);
        return NULL;
    }

    // Ler arquivo inteiro
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    char *conteudo = malloc(tamanho + 1);
    if (!conteudo) {
        fclose(arquivo);
        return NULL;
    }

    fread(conteudo, 1, tamanho, arquivo);
    conteudo[tamanho] = '\0';
    fclose(arquivo);

    printf("[DEBUG] Arquivo lido. Tamanho: %ld bytes\n", tamanho);

    Pergunta **lista = NULL;
    int capacidade = 10;
    int quantidade = 0;

    lista = malloc(sizeof(Pergunta *) * capacidade);

    // Processar cada objeto JSON
    char *pos = conteudo;
    while ((pos = strchr(pos, '{')) != NULL) {
        Pergunta *p = criarPergunta();
        char *fim_objeto = strchr(pos, '}');
        if (!fim_objeto) break;

        // Extrair enunciado
        char *ini = strstr(pos, "\"Enunciado\":");
        if (ini && ini < fim_objeto) {
            ini = strchr(ini, ':');
            if (ini) {
                ini = strchr(ini, '\"');
                if (ini) {
                    ini++;
                    char *fim = strchr(ini, '\"');
                    if (fim && fim < fim_objeto) {
                        int len = fim - ini;
                        p->enunciado = malloc(len + 1);
                        strncpy(p->enunciado, ini, len);
                        p->enunciado[len] = '\0';
                    }
                }
            }
        }

        // Extrair dificuldade
        ini = strstr(pos, "\"Dificuldade\":");
        if (ini && ini < fim_objeto) {
            ini = strchr(ini, ':');
            if (ini) {
                p->dificuldade = atoi(ini + 1);
            }
        }

        // Extrair dica
        ini = strstr(pos, "\"Dica\":");
        if (ini && ini < fim_objeto) {
            ini = strchr(ini, ':');
            if (ini) {
                ini = strchr(ini, '\"');
                if (ini) {
                    ini++;
                    char *fim = strchr(ini, '\"');
                    if (fim && fim < fim_objeto) {
                        int len = fim - ini;
                        p->dica = malloc(len + 1);
                        strncpy(p->dica, ini, len);
                        p->dica[len] = '\0';
                    }
                }
            }
        }

        // Extrair alternativas
        p->numeroAlternativas = 3;
        p->alternativas = malloc(sizeof(char *) * 3);
        
        char *alt_inicio = strstr(pos, "\"Alternativas\":");
        if (alt_inicio && alt_inicio < fim_objeto) {
            int alt_count = 0;
            char *busca = alt_inicio;
            
            while (alt_count < 3 && busca < fim_objeto) {
                char *texto_pos = strstr(busca, "\"Texto\":");
                if (!texto_pos || texto_pos > fim_objeto) break;
                
                texto_pos = strchr(texto_pos, ':');
                if (!texto_pos) break;
                
                texto_pos++;
                while (*texto_pos == ' ' || *texto_pos == '\t' || *texto_pos == '\n') texto_pos++;
                
                if (*texto_pos == '\"') {
                    texto_pos++;
                    char *fim_texto = strchr(texto_pos, '\"');
                    if (fim_texto && fim_texto < fim_objeto) {
                        int len = fim_texto - texto_pos;
                        p->alternativas[alt_count] = malloc(len + 1);
                        strncpy(p->alternativas[alt_count], texto_pos, len);
                        p->alternativas[alt_count][len] = '\0';
                    }
                }
                
                // Verificar se é a resposta correta
                char *correta_pos = strstr(texto_pos, "\"correta\":");
                if (correta_pos && correta_pos < fim_objeto) {
                    char *next_alt = strstr(correta_pos, "\"Texto\":");
                    if (!next_alt || next_alt > fim_objeto) next_alt = fim_objeto;
                    
                    if (strstr(correta_pos, "true") && strstr(correta_pos, "true") < next_alt) {
                        p->resposta_correta = alt_count;
                    }
                }
                
                busca = texto_pos;
                alt_count++;
            }
        }

        // Adicionar à lista
        if (quantidade >= capacidade) {
            capacidade *= 2;
            lista = realloc(lista, sizeof(Pergunta *) * capacidade);
        }
        lista[quantidade++] = p;
        
        pos = fim_objeto + 1;
    }

    free(conteudo);
    *total_perguntas = quantidade;
    printf("[DEBUG] Total de perguntas carregadas: %d\n", quantidade);
    
    // Mostrar distribuição por nível
    int niveis[5] = {0};
    for (int i = 0; i < quantidade; i++) {
        if (lista[i]->dificuldade >= 1 && lista[i]->dificuldade <= 4) {
            niveis[lista[i]->dificuldade]++;
        }
    }
    printf("[DEBUG] Distribuicao por nivel:\n");
    for (int i = 1; i <= 4; i++) {
        printf("[DEBUG]   Nivel %d: %d perguntas\n", i, niveis[i]);
    }
    
    return lista;
}
