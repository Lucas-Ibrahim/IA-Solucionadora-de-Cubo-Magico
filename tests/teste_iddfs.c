#include <stdio.h>

#include "../include/cubo_estado.h"
#include "../include/busca_iddfs.h"

const char *nome_movimento(MovimentoCubo movimento)
{
    switch(movimento){
        case MOV_DIR:     return "DIR";
        case MOV_DIR_INV: return "DIR_INV";
        case MOV_ESQ:     return "ESQ";
        case MOV_ESQ_INV: return "ESQ_INV";
        case MOV_SUP:     return "SUP";
        case MOV_SUP_INV: return "SUP_INV";
        case MOV_INF:     return "INF";
        case MOV_INF_INV: return "INF_INV";
        case MOV_FRT:     return "FRT";
        case MOV_FRT_INV: return "FRT_INV";
        case MOV_TRS:     return "TRS";
        case MOV_TRS_INV: return "TRS_INV";
    }

    return "DESCONHECIDO";
}

int main(void)
{
    EstadoCubo estado;
    CaminhoIDDFS solucao;
    unsigned long estados_visitados;

    estado_inicializar(&estado);

    // Embaralhamento de profundidade 
    estado_aplicar_movimento(&estado, MOV_DIR);
    estado_aplicar_movimento(&estado, MOV_SUP);
    estado_aplicar_movimento(&estado, MOV_FRT);

    int encontrou = busca_iddfs(
        &estado,
        3,
        &solucao,
        &estados_visitados
    );

    printf("Encontrou: %d\n", encontrou);
    printf("Estados visitados: %lu\n", estados_visitados);

    if(encontrou){
        printf("Quantidade de movimentos: %d\n", solucao.tamanho);

        EstadoCubo teste_solucao = estado;

        for(int i = 0; i < solucao.tamanho; i++){
            estado_aplicar_movimento(
                &teste_solucao,
                solucao.movimentos[i]
            );
        }

        printf(
            "Solucao realmente resolve: %d\n",
            estado_resolvido(&teste_solucao)
        );

        printf("Movimentos: ");

        for(int i = 0; i < solucao.tamanho; i++){
            printf("%s ", nome_movimento(solucao.movimentos[i]));
        }   

        printf("\n");

        caminho_liberar(&solucao);
    }

    return 0;
}