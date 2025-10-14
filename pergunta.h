#ifndef PERGUNTA_H
#define PERGUNTA_H

typedef struct {
    char *enunciado;
    char **alternativas;
    int resposta_correta; 
    char *dica;     
    int dificuldade;
    int numeroAlternativas;
} Pergunta;

Pergunta *criarPergunta();
void exibirPergunta(Pergunta *p);
void liberarPergunta(Pergunta *p);

#endif
