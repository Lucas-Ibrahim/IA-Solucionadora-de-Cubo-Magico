#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>
// #include "bibliofilaepilha.h"
#include "cubo_visual.h"

int main()
{
    int opcao;

    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    do
    {
        printf("\n\n");

        printf("\t\t\t+--------------------------------------------------------------------------+\n");
        printf("\t\t\t|                                                                          |\n");
        printf("\t\t\t|                                              /                           |\n");
        printf("\t\t\t|      ____  _   _  ____    ___     __  __    _    ____ ___ ____ ___       |\n");
        printf("\t\t\t|     / ___|| | | || __ )  / _ \\   |  \\/  |  / \\  / ___|_ _/ ___/ _ \\      |\n");
        printf("\t\t\t|    | |    | | | ||  _ \\ | | | |  | |\\/| | / _ \\| |  _ | | |  | | | |     |\n");
        printf("\t\t\t|    | |___ | |_| || |_) || |_| |  | |  | |/ ___ \\ |_| || | |__| |_| |     |\n");
        printf("\t\t\t|     \\____| \\___/ |____/  \\___/   |_|  |_/_/   \\_\\____|___\\____\\___/      |\n");
        printf("\t\t\t|                                                                          |\n");
        printf("\t\t\t|                                2 x 2 x 2                                 |\n");
        printf("\t\t\t|                                                                          |\n");
        printf("\t\t\t|                            1 - Jogo Manual                               |\n");
        printf("\t\t\t|                                                                          |\n");
        printf("\t\t\t|                          2 - Busca em Largura                            |\n");
        printf("\t\t\t|                                                                          |\n");
        printf("\t\t\t|                        3 - Busca em Profundidade                         |\n");
        printf("\t\t\t|                                                                          |\n");
        printf("\t\t\t|                          4 - Busca Heur�stica                            |\n");
        printf("\t\t\t|                                                                          |\n");
        printf("\t\t\t|                                5 - Sair                                  |\n");
        printf("\t\t\t|                                                                          |\n");
        printf("\t\t\t+--------------------------------------------------------------------------+\n");

        printf("\n\t\t\tEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                abrir_jogo_manual();
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");

        }

    } while(opcao != 5);

    return 0;
}
