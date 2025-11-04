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

void cabecalho(const char *t1, const char *t2, int largura)
{
    int cabecalho = largura / 2;

    printf("%-*s", cabecalho, t1);
    printf("%*s", cabecalho, t2);
    printf("\n");
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

void linha2(int largura)
{
    for (int i = 0; i < largura/2; i++)
    {
        Sleep(1);
        printf("--");
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

void direita(const char *texto, int largura)
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
    int moedas = 100;
    int largura = larg();
    int melhort = 0;
    int questao = 1;
    char escolha;
    bool opcao = false;

    int qvida = 1;
    int qdicas = 1;
    int qpular = 1;
    int qtrocar = 1;
    int vidav = 5, dicasv = 5, trocarv = 5, pularv = 5;

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
            char t1[30], t2[30];

            sprintf(t1, "Melhor tentativa: %d", melhort);
            sprintf(t2, "Moedas: %d", moedas);

            system("cls");

            vida = qvida;
            fflush(stdin);

            linha(largura);
            Sleep(250);
            cabecalho(t1, t2, largura);
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

        int dicas = qdicas;
        int pular = qpular;
        int trocar = qtrocar;

        switch (escolha)
        {
        case 'A':
            do
            {
                opcao = true;

                char altn;

                char vidas[30];
                sprintf(vidas, "Vidas: %d", vida);

                char f1[30], f2[30], f3[30];
                sprintf(f1, "[1] Dicas: %d", dicas);
                sprintf(f2, "[2] Trocar questão: %d", trocar);
                sprintf(f3, "[3] Pular nível: %d", pular);
                
                system("cls");
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
        {
            char compra;
            do
            {
                vida = qvida;
                opcao = true;

                char t1[30], t2[30];
                sprintf(t1, "<- Sair[S]");
                sprintf(t2, "Moedas: %d", moedas);

                char dica[40],pulos[40],troca[40], vidas[40];
                sprintf(vidas,"[V] +1 Vidas (%02d/05)    valor:%02d\n", vida, vidav);
                sprintf(dica,"[D] +1 Dicas (%d/3)     valor:%d\n",dicas, dicasv);
                sprintf(pulos,"[P] +1 Pular (%d/3)    valor:%d\n",pular, pularv);
                sprintf(troca,"[T] +1 Trocar (%d/3)   valor:%d\n",trocar, trocarv);


                system("cls");
                linha2(largura);
                cabecalho(t1, t2, largura);

                center(vidas, largura);
                center(dica, largura);
                center(pulos, largura);
                center(troca, largura);

                linha2(largura);

                fflush(stdin);
                scanf("%c", &compra);

                if (compra == 'V'){
                    compra = 'v';
                }
                if (compra == 'D'){
                    compra = 'd';
                }
                if (compra == 'P'){
                    compra = 'p';
                }
                if (compra == 'T'){
                    compra = 't';
                }
                if (compra == 'S'){
                    compra = 's';
                }


                switch (compra)
                {
                case 'v':
                    if (vida < 5)
                    {
                        if (moedas >= vidav)
                        {
                            moedas = moedas - vidav;
                            qvida++;
                            vidav = vidav + 5;
                        }
                        else
                        {
                            linha(largura);
                            center("Valor insuficiente!!",largura);
                            linha(largura);
                            Sleep(3000);
                        }
                    }
                    else
                    {
                        linha(largura);
                        center("Você atingiu o limite de vidas",largura);
                        linha(largura);
                        Sleep(3000);
                    }
                    break;

                case 'd':
                    if (dicas < 3)
                    {
                        if (moedas >= dicasv)
                        {
                            moedas = moedas - dicasv;
                            qdicas++;
                            dicasv =+ 5;
                        }
                        else
                        {
                            linha(largura);
                            center("Valor insuficiente!!", largura);
                            linha(largura);
                            Sleep(3000);
                        }
                    }
                    else
                    {
                        linha(largura);
                        center("Você atingiu o limite de dicas", largura);
                        linha(largura);
                        Sleep(3000);
                    }
                    break;

                case 'p':
                    if (pularv < 3)
                    {
                        if (moedas >= pularv)
                        {
                            moedas = moedas - pularv;
                            pular++;
                            pularv =+ 5;
                        }
                        else
                        {
                            linha(largura);
                            center("Valor insuficiente!!", largura);
                            linha(largura);
                            Sleep(3000);
                        }
                    }
                    else
                    {
                        linha(largura);
                        center("Você atingiu o limite de pulos", largura);
                        linha(largura);
                        Sleep(3000);
                    }
                    break;

                case 't':
                    if (trocar < 3)
                    {
                        if (moedas >= trocarv)
                        {
                            moedas = moedas - trocarv;
                            vida++;
                             trocarv =+ 5;
                        }
                        else
                        {
                            linha(largura);
                            center("Valor insuficiente!!", largura);
                            linha(largura);
                            Sleep(3000);
                        }
                    }
                    else
                    {
                        linha(largura);
                        center("Você atingiu o limite de trocas",largura);
                        linha(largura);
                        Sleep(3000);
                    }
                    break;


                    case 's':
                    opcao = false;

                    break;
                default:

                    linha(largura);
                    center("Opção invalida!!",largura);
                    linha(largura);
                    Sleep(3000);

                    break;
                }

            } while (opcao == true);
        }
        }

    } while (opcao == false);

    return 0;
}
