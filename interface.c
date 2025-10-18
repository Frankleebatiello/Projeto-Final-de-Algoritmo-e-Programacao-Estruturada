#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

void linha(int largura)
{
    for (int i = 0; i < largura; i++)
        printf("-");
    printf("\n");
}

void center(const char *texto, int largura)
{
    int tamanho = strlen(texto);
    int inicio = (largura - tamanho) / 2;
    if (inicio < 0)
        inicio = 0;

    for (int i = 0; i < inicio; i++)
        printf(" ");
    printf("%s\n", texto);
}

void esquerda(const char *texto, int largura)
{
    int tamanho = strlen(texto);
    int inicio = (largura - tamanho);
    if (inicio < 0)
        inicio = 0;

    for (int i = 0; i < inicio; i++)
        printf(" ");
    printf("%s\n", texto);
}

int main()
{
    int largura = 138;
    int vida = 1;
    int melhort = 0;
    char escolha;
    bool opcao = false;

    system("cls");

    linha(largura);
    center("Bem Vindo!!", largura);
    center("Dev Game Quest!!", largura);
    linha(largura);

    system("pause");
    

    do{
    system("cls");

    linha(largura);
    printf("Melhor Tentativa:%d \n",melhort);
    printf("Vidas:%d \n",vida);
    center("Dev Game Quest!!\n", largura);
    center("Começar [A]", largura);
    center("Loja [L]", largura);
    center("Sair [S]", largura);
    linha(largura);
    
    fflush(stdin);
    scanf("%c", &escolha);


if(escolha == 'a'){
    escolha = 'A';
}
if(escolha == 'l'){
    escolha = 'L';
}
if(escolha == 's'){
    escolha = 'S';
}


if(escolha == 'A'||escolha == 'L'|| escolha == 'S'){
opcao = true;
}
else{
    system("cls");
   printf("opção invalida!\n");
   system("pause");
   opcao = false;
}


}while (opcao == false);
    


switch (escolha)
{
case 'A':
    puts("voce escolheu a");
    break;

case 'S':
    puts("voce escolheu s");
    break;
    
case 'L':
    puts("voce escolheu l");
    break;    
}

return 0;
}