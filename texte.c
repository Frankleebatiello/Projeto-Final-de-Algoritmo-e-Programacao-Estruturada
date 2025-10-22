#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALTERNATIVAS 4
#define TAMANHO_MAX 600

typedef struct // Alternativa
{
    char alternativa[MAX_ALTERNATIVAS];
    char texto[TAMANHO_MAX];
    bool correta;
} alt;

typedef struct // Pergunta
{
    char enunciado[TAMANHO_MAX];
    alt alternativas[MAX_ALTERNATIVAS];
    int numeroAlternativas;
    char dica[TAMANHO_MAX];
    int dificuldade;
    bool jaUsada;
} pgt;

typedef struct // Banco de Perguntas
{
    pgt *questoes;
    int quantidadePgt;
    int capacidade;
} bQ;

char *encontrarProx(char *str, const char *padrao)
{
    return strstr(str, padrao);
}

void extrairTextoEntreAspas(char *fonte, char *destino, int maxLen)
{
    char *inicio = strstr(fonte, "\"");
    if (!inicio)
    {
        destino[0] = '\0';
        return;
    }

    inicio++;

    char *fim = strchr(inicio, '"');
    if (!fim)
    {
        destino[0] = '\0';
        return;
    }

    int len = fim - inicio;
    if (len >= maxLen)
    {
        len = maxLen - 1;
    }

    strncpy(destino, inicio, len);
    destino[len] = '\0';
}

int extrairBooleano(char *fonte)
{
    char *valorTrue = strstr(fonte, "true");
    char *valorFalse = strstr(fonte, "false");

    if (valorTrue && (!valorFalse || valorTrue < valorFalse))
    {
        return 1;
    }
    return 0;
}

int extrairInteiro(char *fonte)
{
    char *aux = fonte;
    while (*aux && (*aux < '0' || *aux > '9'))
    {
        aux++;
    }
    return atoi(aux);
}

void inicializarBanco(bQ *banco)
{
    banco->capacidade = 10;
    banco->quantidadePgt = 0;
    banco->questoes = (pgt *)malloc(banco->capacidade * sizeof(pgt));
    if (!banco->questoes)
    {
        printf("Erro: Falha ao alocar memoria!\n");
        exit(1);
    }
}

void expandirBanco(bQ *banco)
{
    banco->capacidade *= 2;
    pgt *novoArray = (pgt *)realloc(banco->questoes, banco->capacidade * sizeof(pgt));
    if (!novoArray)
    {
        printf("Erro: Falha ao realocar memoria!\n");
        exit(1);
    }

    banco->questoes = novoArray;
}

int parseJson(const char *conteudoJson, bQ *banco)
{
    char *conteudo = strdup(conteudoJson);
    char *ptr = conteudo;

    // Encontra o início do array de perguntas
    ptr = encontrarProx(ptr, "\"Perguntas\"");
    if (!ptr)
    {
        free(conteudo);
        return 0;
    }

    ptr = encontrarProx(ptr, "[");
    if (!ptr)
    {
        free(conteudo);
        return 0;
    }
    ptr++;

    // Processa cada questão
    while (1)
    {
        // Procura próximo objeto de questão
        char *inicioPgt = encontrarProx(ptr, "{");
        if (!inicioPgt)
            break;

        char *fimPgt = encontrarProx(inicioPgt, "}");
        if (!fimPgt)
            break;

        // Verifica se chegamos ao fim do array
        char *arrayFim = strchr(ptr, ']');
        if (arrayFim && arrayFim < inicioPgt)
            break;

        if (banco->quantidadePgt >= banco->capacidade)
        {
            expandirBanco(banco); // Corrigido nome da função
        }

        pgt *q = &banco->questoes[banco->quantidadePgt];
        q->jaUsada = 0; // Inicializa como não usada
        q->numeroAlternativas = 0; // Corrigido typo: numoAlternativas

        // Extrai enunciado
        char *enunciado_pos = encontrarProx(inicioPgt, "\"enunciado\"");
        if (enunciado_pos && enunciado_pos < fimPgt)
        {
            extrairTextoEntreAspas(enunciado_pos + 11, q->enunciado, TAMANHO_MAX); // Nome corrigido
        }

        // Extrai alternativas
        char *altArrayInicio = encontrarProx(inicioPgt, "\"alternativas\"");
        if (altArrayInicio && altArrayInicio < fimPgt)
        {
            altArrayInicio = encontrarProx(altArrayInicio, "[");
            char *altArrayFim = encontrarProx(altArrayInicio, "]");

            char *alt_ptr = altArrayInicio + 1;
            while (q->numeroAlternativas < MAX_ALTERNATIVAS)
            {
                char *altInicio = encontrarProx(alt_ptr, "{");
                if (!altInicio || altInicio > altArrayFim)
                    break;

                char *altFim = encontrarProx(altInicio, "}");
                if (!altFim || altFim > altArrayFim)
                    break;

                alt *alternativa = &q->alternativas[q->numeroAlternativas]; // Tipo correto: alt

                // Extrai letra da alternativa
                char *altLetra = encontrarProx(altInicio, "\"alternativa\"");
                if (altLetra && altLetra < altFim)
                {
                    extrairTextoEntreAspas(altLetra + 13, alternativa->alternativa, 4); // Nome corrigido
                }

                // Extrai texto da alternativa
                char *altTexto = encontrarProx(altInicio, "\"texto\"");
                if (altTexto && altTexto < altFim)
                {
                    extrairTextoEntreAspas(altTexto + 7, alternativa->texto, TAMANHO_MAX); // Nome corrigido
                }

                // Extrai se é correta
                char *altCorreta = encontrarProx(altInicio, "\"correta\"");
                if (altCorreta && altCorreta < altFim)
                {
                    alternativa->correta = extrairBooleano(altCorreta + 9); // Nome corrigido
                }

                q->numeroAlternativas++; // Nome consistente
                alt_ptr = altFim + 1;
            }
        }
        
        // Extrai dica
        char *dicaPgt = encontrarProx(inicioPgt, "\"dica\"");
        if (dicaPgt && dicaPgt < fimPgt)
        {
            extrairTextoEntreAspas(dicaPgt + 6, q->dica, TAMANHO_MAX); // Nome corrigido
        }

        // Extrai dificuldade
        char *dificuldadePgt = encontrarProx(inicioPgt, "\"dificuldade\""); // Corrigido typo: difivuldadePgt
        if (dificuldadePgt && dificuldadePgt < fimPgt)
        {
            q->dificuldade = extrairInteiro(dificuldadePgt + 13); // Nome corrigido
        }

        banco->quantidadePgt++;
        ptr = fimPgt + 1;
    }

    free(conteudo);
    return banco->quantidadePgt;
}

pgt *extrairQuestao(bQ *banco, int indice)
{
    if (indice < 0 || indice >= banco->quantidadePgt)
    {
        printf("Erro: Indice invalido!\n");
        return NULL;
    }

    if (banco->questoes[indice].jaUsada)
    {
        printf("Erro: Esta questao ja foi usada!\n");
        return NULL;
    }

    // Marca a questão como usada
    banco->questoes[indice].jaUsada = 1;

    return &banco->questoes[indice];
}

pgt *extrairPgtDificuldade(bQ *banco, int nivel)
{
    if (nivel < 0 || nivel > 4)
    {
        printf("Erro: Nivel de dificuldade invalido! Use valores entre 0 e 4.\n");
        return NULL;
    }

    for (int i = 0; i < banco->quantidadePgt; i++)
    {
        if (banco->questoes[i].dificuldade == nivel && !banco->questoes[i].jaUsada)
        {
            banco->questoes[i].jaUsada = 1;
            return &banco->questoes[i];
        }
    }

    printf("Erro: Nenhuma questao disponivel com dificuldade %d\n", nivel);
    return NULL;
}

void resetarQuestoes(bQ *banco)
{
    for (int i = 0; i < banco->quantidadePgt; i++)
    {
        banco->questoes[i].jaUsada = 0;
    }
}

void exibirQuestao(pgt *q)
{
    if (!q)
    {
        return;
    }

    printf("\n=== QUESTAO ===\n");
    printf("Enunciado: %s\n", q->enunciado);
    printf("Dificuldade: %d\n\n", q->dificuldade);

    printf("Alternativas:\n");
    for (int i = 0; i < q->numeroAlternativas; i++)
    {
        printf("  %s %s %s\n",
               q->alternativas[i].alternativa,
               q->alternativas[i].texto,
               q->alternativas[i].correta ? "[CORRETA]" : "");
    }
    
    printf("\nDica: %s\n", q->dica);
    printf("===============\n\n");
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

// Função auxiliar para ler arquivo JSON
char *lerArquivo(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo)
    {
        printf("Erro ao abrir arquivo: %s\n", nomeArquivo);
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    char *conteudo = (char *)malloc(tamanho + 1);
    if (!conteudo)
    {
        fclose(arquivo);
        return NULL;
    }

    fread(conteudo, 1, tamanho, arquivo);
    conteudo[tamanho] = '\0';

    fclose(arquivo);
    return conteudo;
}

int main()
{
    bQ banco;
    inicializarBanco(&banco);

    // Carrega perguntas do arquivo JSON
    char *jsonContent = lerArquivo("perguntas.json");
    if (!jsonContent)
    {
        printf("Erro ao carregar perguntas!\n");
        return 1;
    }

    int numPerguntas = parseJson(jsonContent, &banco);
    printf("Carregadas %d perguntas com sucesso!\n\n", numPerguntas);
    free(jsonContent);

    // Exemplo de uso: extrair perguntas por dificuldade
    printf("=== TESTANDO PERGUNTAS DE DIFICULDADE 1 ===\n");
    pgt *q1 = extrairPgtDificuldade(&banco, 1);
    if (q1)
    {
        exibirQuestao(q1);
    }

    printf("=== TESTANDO PERGUNTAS DE DIFICULDADE 2 ===\n");
    pgt *q2 = extrairPgtDificuldade(&banco, 2);
    if (q2)
    {
        exibirQuestao(q2);
    }

    // Resetar questões para reutilizar
    resetarQuestoes(&banco);
    printf("\n=== QUESTOES RESETADAS ===\n");

    // Extrair por índice
    printf("\n=== EXTRAINDO QUESTAO POR INDICE (0) ===\n");
    pgt *q3 = extrairQuestao(&banco, 0);
    if (q3)
    {
        exibirQuestao(q3);
    }

    // Liberar memória
    liberarBanco(&banco);
    printf("Memoria liberada com sucesso!\n");

    return 0;
}

