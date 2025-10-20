#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

int larg()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int largura = 0;

    while (true)
    {
        if (GetConsoleScreenBufferInfo(hConsole, &csbi))
        {
            largura = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            if (largura > 0)
                return largura;
        }
    }
}

void rodape(const char *f1, const char *f2, const char *f3, int largura)
{
    int rodape = largura / 3;

    printf("%-*s", rodape, f1);
    printf("%-*s", rodape, f2);
    printf("%-*s\n", rodape, f3);
}

void linha(int largura)
{
    for (int i = 0; i < largura; i++)
    {
        Sleep(1);
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
    int largura = larg();

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

    do
    {
        int vida;
        do
        {
            system("cls");

            vida = 1;
            fflush(stdin);

            linha(largura);
            Sleep(250);
            printf("Melhor Tentativa:%d \n", melhort);
            Sleep(250);
            printf("Vidas:%d \n", vida);
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

            if (escolha == 'a')
            {
                escolha = 'A';
            }
            if (escolha == 'l')
            {
                escolha = 'L';
            }
            if (escolha == 's')
            {
                escolha = 'S';
            }

            if (escolha == 'A' || escolha == 'L' || escolha == 'S')
            {
                opcao = true;
            }
            else
            {

                system("cls");
                printf("opção invalida!\n");
                system("pause");
                opcao = false;
            }

        } while (opcao == false);

        int dicas = 1;
        int pular = 1;
        int trocar = 1;

        switch (escolha)
        {
        case 'A':
            do
            {
                opcao = true;

                char altn;
                system("cls");

                char vidas[10];
                sprintf(vidas, "Vidas: %d", vida);

                char f1[30], f2[30], f3[30];

                sprintf(f1, "[1] Dicas: %d", dicas);
                sprintf(f2, "[2] Trocar questão: %d", trocar);
                sprintf(f3, "[3] Pular nível: %d", pular);

                linha(largura);
                center(vidas, largura);
                printf("Questão %d\n", questao);

                puts("\naqui ficaram as perguntas ex: quanto é 1+1?\n");

                printf("a) 2\n");
                printf("b) 3\n\n");
                rodape(f1, f2, f3, largura);
                linha(largura);

                fflush(stdin);
                scanf("%c", &altn);

                if (altn == 'a')
                {
                    altn = 'A';
                }
                if (altn == 'b')
                {
                    altn = 'B';
                }

                switch (altn)
                {
                case 'A':
                    system("cls");
                    linha(largura);
                    center("Voce acertou!!", largura);
                    linha(largura);
                    questao++;
                    opcao = true;

                    break;

                case 'B':
                    system("cls");

                    linha(largura);
                    center("Voce errou!!", largura);
                    linha(largura);
                    vida--;
                    opcao = true;

                    if (vida <= 0)
                    {
                        system("cls");

                        linha(largura);
                        center("Suas vidas acabaram!!", largura);
                        center("Você perdeu!", largura);
                        center("Estude mais!!", largura);
                        center("Ou compre mais vidas na loja!!!", largura);
                        linha(largura);

                        opcao = false;
                    }

                    break;

                case '1':

                    linha(largura);
                    center("Voce está pedindo dica para 1+1?", largura);
                    center("Tu é burro pra CARALHOO!!", largura);
                    linha(largura);

                    dicas--;

                    Sleep(3000);
                    opcao = true;

                    break;

                case '2':

                    linha(largura);
                    center("Voce está pedindo pra trocar uma questão de 1+1?", largura);
                    center("VSF!! MUITO BURRO HAHAHAHA!!!", largura);
                    linha(largura);

                    trocar--;

                    Sleep(3000);
                    opcao = true;

                    break;
                case '3':

                    linha(largura);
                    center("Voce está para pular em 1+1?", largura);
                    center("Namoral, VSF", largura);
                    linha(largura);

                    pular--;

                    Sleep(3000);
                    opcao = true;

                    break;

                default:
                    system("cls");
                    linha(largura);
                    center("Opção invalida!!", largura);
                    linha(largura);
                    break;
                }

            } while (opcao == true);

            break;

        case 'S':
            puts("voce escolheu s");
            break;

        case 'L':
            puts("voce escolheu l");
            break;
        }
    } while (opcao == false);
    return 0;
}