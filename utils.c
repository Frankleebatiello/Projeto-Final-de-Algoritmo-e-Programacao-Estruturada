#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "utils.h"

void limparBuffer()
{
    int l;
    while ((l = getchar()) != '\n' && l != EOF);
}

int larguraTerminal()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO CSBI;
    int larg = 0;

    while (true)
    {
        if (GetConsoleScreenBufferInfo(hConsole, &CSBI))
        {
            larg = CSBI.srWindow.Right - CSBI.srWindow.Left + 1;
            if (larg > 0)
            {
                return larg;
            }
            else
            {
                printf("Tamanho do terminal insuficiente!!!");
            }
        }
    }
}

void rodape(const char *fracao1, const char *fracao2, const char *fracao3, int largura)
{
    int rodape = largura / 3;

    printf("%-*s", rodape, fracao1);
    printf("%-*s", rodape, fracao2);
    printf("%-*s\n", rodape, fracao3);
}

void centralizarTexto(const char* texto, int largura)
{
    int comprimento = strlen(texto);
    int espacos = (largura - comprimento) / 2;
    if (espacos < 0)
    {
        espacos = 0;
    }
    
    printf("\n");
    for (int i = 0; i < espacos; i++)
    {
        printf(" ");
    }
    printf("%s", texto);
    
}

void preencher(int largura, char caractere)
{
    for (int i = 0; i < largura; i++)
    {
        Sleep(0.5);
        printf("%c", caractere);
    }
}

void alinharEsquerda(const char *texto, int largura)
{
    int comprimento = strlen(texto);
    int espacos = largura / 4;

    for (int i = 0; i < espacos; i++)
    {
        printf(" ");
    }
    
    printf("%s\n", texto);
}