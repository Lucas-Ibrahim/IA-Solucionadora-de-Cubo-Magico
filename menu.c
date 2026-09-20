#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>
// #include "bibliofilaepilha.h"
#include "cubo_visual.h"
#include "busca_bfs.h"

const char *nome_movimento(MovimentoCubo movimento)
{
    switch (movimento)
    {
        case MOV_DIR:
            return "DIR"; /* direita */

        case MOV_DIR_INV:
            return "DIR_INV"; /* gira a face direita no sentido ao contrario*/

        case MOV_ESQ:
            return "ESQ"; /* esquerda */

        case MOV_ESQ_INV:
            return "ESQ_INV"; /* gira a face esquerda no sentido contrario */

        case MOV_SUP:
            return "SUP"; /* gira a face de cima */

        case MOV_SUP_INV:
            return "SUP_INV"; /* gira a face de cima no sentido contrario */

        case MOV_INF:
            return "INF"; /* gira a face de baixo */

        case MOV_INF_INV:
            return "INF_INV"; /* gira a face de baixo no sentido contrario */

        case MOV_FRT:
            return "FRT"; /* gira a face da frente */

        case MOV_FRT_INV:
            return "FRT_INV"; /* gira a face da frente no sentido contrario */

        case MOV_TRS:
            return "TRS"; /* gira a face de tras */

        case MOV_TRS_INV:
            return "TRS_INV"; /* gira a face de tras no sentido contrario */

        default:
            return "DESCONHECIDO";
    }
}

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
                {
                EstadoCubo cubo;

                /* inicia o cubo resolvido */
                estado_inicializar(&cubo);

                /* embaralha o cubo para testar a BFS */
                estado_aplicar_movimento(&cubo, MOV_DIR);
                estado_aplicar_movimento(&cubo, MOV_SUP);
                estado_aplicar_movimento(&cubo, MOV_FRT);

                printf("\nIniciando Busca em Largura...\n");

                /* chama a busca em largura */
                ResultadoBusca resultado = busca_bfs(&cubo);

                if (resultado.no_final != NULL)
                {
                    printf("\nSolucao encontrada!\n");
                    printf("Estados analisados: %d\n",resultado.estados_visitados);

                    MovimentoCubo caminho[20];

                    int quantidade = busca_reconstruir_caminho( resultado.no_final,caminho,20);

                    printf("Quantidade de movimentos: %d\n", quantidade);

                    for (int i = 0; i < quantidade; i++)
                    {
                        printf("Movimento %d: %s\n",i + 1,nome_movimento(caminho[i]));
                    }
                }
                else
                {
                    printf("\nNao foi encontrada uma solucao.\n");
                }

                break;
            }

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
