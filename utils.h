#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

void limparBuffer();

int larguraTerminal();

void rodape(const char *fracao1, const char *fracao2, const char *fracao3, int largura);

void centralizarTexto(const char* texto, int largura);

void preencher(int largura, char caractere);

void alinharEsquerda(const char *texto, int largura);

void converter (char *letra[1], int *numero);

#endif