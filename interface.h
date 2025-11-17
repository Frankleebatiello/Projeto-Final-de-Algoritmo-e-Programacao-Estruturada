#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include "utils.h"

void exibirTitulo(int largura);

void cabecalho(const char *texto1, const char *texto2, int largura);

void exibirRegras(int largura);

void exibirMenu(int largura);

void exibirMenu2(int largura);

int sair(int largura, const char *comentario);

void desenvolvedores (int largura);

void comentario (int largura, char *comentario);


#endif