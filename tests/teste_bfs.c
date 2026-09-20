#include <stdio.h>
#include "cubo_estado.h"
#include "busca_bfs.h"

int main(void)
{
    EstadoCubo cubo;

    estado_inicializar(&cubo); /* cria o cubo no estado resolvido */

    printf("Antes de embaralhar:\n");

    if (estado_resolvido(&cubo))
    {
        printf("Cubo resolvido!\n");
    }

    estado_aplicar_movimento(&cubo, MOV_DIR); /* faz apenas um movimento para embaralhar */
    estado_aplicar_movimento(&cubo, MOV_SUP);
    estado_aplicar_movimento(&cubo, MOV_FRT);

   printf("\nDepois de fazer MOV_DIR, MOV_SUP e MOV_FRT:\n");

    if (!estado_resolvido(&cubo))
    {
        printf("Cubo embaralhado!\n");
    }

    ResultadoBusca resultado = busca_bfs(&cubo); /* chama a nossa busca em largura */

    if (resultado.no_final != NULL)
    {
        printf("\nBFS encontrou uma solucao!\n");
        printf("Estados visitados: %d\n", resultado.estados_visitados);

        MovimentoCubo caminho[20];

        
        int quantidade = busca_reconstruir_caminho( resultado.no_final,caminho,20); /* pega os movimentos encontrados pela busca */

        printf("Quantidade de movimentos da solucao: %d\n", quantidade);

        for (int i = 0; i < quantidade; i++) /* mostra os movimentos encontrados */
        {
            printf("Movimento %d: %d\n", i + 1, caminho[i]);
        }
    }
    else
    {
        printf("\nBFS nao encontrou uma solucao.\n");
    }

    return 0;
}