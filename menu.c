#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
// #include "bibliofilaepilha.h"
#include "cubo_visual.h"
#include "busca_bfs.h"
#include "busca_iddfs.h"
#include "busca_astar.h"

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

// Mantem o mesmo embaralhamento nas duas buscas quando a seed e repetida.
#define QUANTIDADE_EMBARALHAMENTO 4

static int preparar_embaralhamento(EstadoCubo *cubo, MovimentoCubo embaralhamento[QUANTIDADE_EMBARALHAMENTO])
{
    unsigned int seed;
    printf("\nDigite a seed do embaralhamento: ");
    if (scanf("%u", &seed) != 1)
    {
        printf("Seed invalida.\n");
        return 0;
    }

    estado_inicializar(cubo);
    estado_gerar_embaralhamento(seed, embaralhamento, QUANTIDADE_EMBARALHAMENTO);
    printf("Embaralhamento (seed %u):", seed);
    for (int i = 0; i < QUANTIDADE_EMBARALHAMENTO; i++)
    {
        estado_aplicar_movimento(cubo, embaralhamento[i]);
        printf(" %s", nome_movimento(embaralhamento[i]));
    }
    printf("\n");
    return 1;
}

int main()
{
    int opcao;

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
        printf("\t\t\t|                          4 - Busca Heuristica                           |\n");
        printf("\t\t\t|                                                                          |\n");
        printf("\t\t\t|                                5 - Sair                                  |\n");
        printf("\t\t\t|                                                                          |\n");
        printf("\t\t\t+--------------------------------------------------------------------------+\n");

        printf("\n\t\t\tEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            abrir_jogo_manual();
            break;

        case 2:
        {
            EstadoCubo cubo;

            MovimentoCubo embaralhamento[QUANTIDADE_EMBARALHAMENTO];
            int quantidade_embaralhamento = QUANTIDADE_EMBARALHAMENTO;
            if (!preparar_embaralhamento(&cubo, embaralhamento))
                break;

            printf("\nIniciando Busca em Largura...\n");

            ResultadoBusca resultado = busca_bfs(&cubo);

            if (resultado.no_final != NULL)
            {
                printf("\nSolucao encontrada!\n");
                printf("Estados analisados: %d\n", resultado.estados_visitados);

                MovimentoCubo caminho[20];

                int quantidade = busca_reconstruir_caminho(resultado.no_final, caminho, 20);
                liberar_nos(resultado.todos_nos);
                printf("Quantidade de movimentos: %d\n", quantidade);

                for (int i = 0; i < quantidade; i++)
                {
                    printf("Movimento %d: %s\n", i + 1, nome_movimento(caminho[i]));
                }

                // agora que ja imprimimos os movimentos no terminal, abre a janela e mostra o cubo embaralhando e depois se resolvendo
                abrir_visualizacao_solucao(embaralhamento, quantidade_embaralhamento, caminho, quantidade);
            }
            else
            {
                printf("\nNao foi encontrada uma solucao.\n");
            }

            break;
        }

        case 3:
        {
            EstadoCubo cubo;

            MovimentoCubo embaralhamento[QUANTIDADE_EMBARALHAMENTO];
            int quantidade_embaralhamento = QUANTIDADE_EMBARALHAMENTO;
            if (!preparar_embaralhamento(&cubo, embaralhamento))
                break;

            printf("\nIniciando Busca em Profundidade Limitada Iterativa...\n");

            ResultadoBusca resultado = busca_iddfs(&cubo, 10);

            if (resultado.no_final != NULL)
            {
                printf("\nSolucao encontrada!\n");
                printf("Estados analisados: %d\n", resultado.estados_visitados);

                MovimentoCubo caminho[20];
                
                int quantidade = busca_reconstruir_caminho(resultado.no_final, caminho, 20);
                liberar_nos(resultado.todos_nos);
                printf("Quantidade de movimentos: %d\n", quantidade);

                for (int i = 0; i < quantidade; i++)
                {
                    printf("Movimento %d: %s\n", i + 1, nome_movimento(caminho[i]));
                }

                abrir_visualizacao_solucao(embaralhamento, quantidade_embaralhamento, caminho, quantidade);
            }
            else
            {
                printf("\nNao foi encontrada uma solucao.\n");
            }

            break;
        }

        case 4:
        {
            EstadoCubo cubo;

            MovimentoCubo embaralhamento[QUANTIDADE_EMBARALHAMENTO];

            int quantidade_embaralhamento =
                QUANTIDADE_EMBARALHAMENTO;

            if (!preparar_embaralhamento(
                    &cubo,
                    embaralhamento))
                break;

            printf(
                "\nIniciando Busca Heuristica...\n");

            ResultadoBusca resultado =
                busca_astar(&cubo);

            if (resultado.no_final != NULL)
            {
                printf(
                    "\nSolucao encontrada!\n");

                printf(
                    "Estados analisados: %d\n",
                    resultado.estados_visitados);

                MovimentoCubo caminho[20];

                int quantidade =
                    busca_reconstruir_caminho(
                        resultado.no_final,
                        caminho,
                        20);
                
                liberar_nos(resultado.todos_nos);

                printf(
                    "Quantidade de movimentos: %d\n",
                    quantidade);

                for (int i = 0;
                     i < quantidade;
                     i++)
                {
                    printf(
                        "Movimento %d: %s\n",
                        i + 1,
                        nome_movimento(caminho[i]));
                }

                abrir_visualizacao_solucao(
                    embaralhamento,
                    quantidade_embaralhamento,
                    caminho,
                    quantidade);
            }
            else
            {
                printf(
                    "\nNao foi encontrada uma solucao.\n");
            }

            break;
        }

        case 5:
            printf("\nSaindo...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 5);

    return 0;
}
