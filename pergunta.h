typedef struct {
    char *enunciado;
    char **alternativas[4];
    int resposta_correta; 
    char *dica;     
    int dificuldade;
} Pergunta;