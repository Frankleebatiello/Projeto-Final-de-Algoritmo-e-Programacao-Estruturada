#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "pergunta.h"
#include "json.h"

int sortearPergunta()
{
    int numero;

    srand(time(NULL);

    numero = rand() % 100;

    return numero; // numero precisa ser diferente a cada interação, pois se não a questão repete
}

void inicializarEmbaralhar(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = i;
    }

    srand(time(NULL));
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int aux = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = aux;
    }
}

void definirTamanho ()
{

    int contadorLinhas = 0;
    int linhaLida;

    FILE *arquivoJson = fopen("perguntas.json", "r");

    if (arquivoJson == NULL)
    {
        perror("Erro ao abrir o arquivo!");
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
}

int main() {
    int tamanho = 100;
    int vetor[tamanho];

    inicializarEmbaralhar(vetor, tamanho);

    // Exibe o vetor embaralhado
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }

    return 0;
}
