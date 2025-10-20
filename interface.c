#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

void linha(int largura)
{
    for (int i = 0; i < largura; i++){
    Sleep(10); 
        printf("-"); 
    }
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
    int questao = 1;
    char escolha;
    bool opcao = false;



    system("cls");

    linha(largura);
    Sleep(250);
    center("Bem Vindo!!", largura);
    Sleep(250);
    center("Dev Game Quest!!", largura);
    Sleep(250);
    linha(largura);

    system("pause");
    

    do{
    system("cls");

    linha(largura);
    Sleep(250);
    printf("Melhor Tentativa:%d \n",melhort);
    Sleep(250);
    printf("Vidas:%d \n",vida);
    Sleep(250);
    center("Dev Game Quest!!\n", largura);
    Sleep(250);
    center("Começar [A]", largura);
    Sleep(250);
    center("Loja [L]", largura);
    Sleep(250);
    center("Sair [S]", largura);
    Sleep(250);
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
   do{

    system("cls");

    char vidas[10];
    sprintf(vidas,"Vidas: %d", vida);

    linha(largura);
    center(vidas, largura);
    printf("Questão %d\n", questao);

    center("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",largura);

    linha(largura);



   }while (opcao == false);
   


    
    
    
    
    
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