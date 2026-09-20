#include <stdio.h>

#include "../include/cubo_estado.h"
#include "../include/busca_iddfs.h"
#include "../include/laco_generico.h"


static const char *nome_movimento(MovimentoCubo movimento)
{
    switch(movimento)
    {
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


/*
    Verifica se os movimentos encontrados pela busca
    realmente levam o cubo até o estado resolvido.
*/
static int verificar_solucao(
    const EstadoCubo *estado_inicial,
    ResultadoBusca resultado
)
{
    if(resultado.no_final == NULL)
    {
        return 0;
    }

    MovimentoCubo movimentos[100];

    int quantidade = busca_reconstruir_caminho(
        resultado.no_final,
        movimentos,
        100
    );

    EstadoCubo teste = *estado_inicial;

    for(int i = 0; i < quantidade; i++)
    {
        estado_aplicar_movimento(
            &teste,
            movimentos[i]
        );
    }

    return estado_resolvido(&teste);
}


/*
    Mostra os dados da solução encontrada.
*/
static void mostrar_resultado(
    const EstadoCubo *estado_inicial,
    ResultadoBusca resultado
)
{
    printf("Estados visitados: %d\n",
           resultado.estados_visitados);

    if(resultado.no_final == NULL)
    {
        printf("Solucao encontrada: NAO\n");
        return;
    }

    printf("Solucao encontrada: SIM\n");

    MovimentoCubo movimentos[100];

    int quantidade = busca_reconstruir_caminho(
        resultado.no_final,
        movimentos,
        100
    );

    printf("Quantidade de movimentos: %d\n", quantidade);

    printf("Movimentos: ");

    for(int i = 0; i < quantidade; i++)
    {
        printf("%s ", nome_movimento(movimentos[i]));
    }

    printf("\n");

    printf(
        "Solucao realmente resolve: %d\n",
        verificar_solucao(estado_inicial, resultado)
    );
}


int main(void)
{
    EstadoCubo estado;


    /*
        TESTE 1
        Cubo já resolvido.
        Deve encontrar com limite 0.
    */
    printf("\n===== TESTE 1 =====\n");

    estado_inicializar(&estado);

    ResultadoBusca teste1 =
        busca_iddfs(&estado, 0);

    mostrar_resultado(&estado, teste1);


    /*
        TESTE 2
        Cubo embaralhado com 1 movimento.
        Limite 0 não deve encontrar.
    */
    printf("\n===== TESTE 2 =====\n");

    estado_inicializar(&estado);
    estado_aplicar_movimento(&estado, MOV_DIR);

    ResultadoBusca teste2 =
        busca_iddfs(&estado, 0);

    mostrar_resultado(&estado, teste2);


    /*
        TESTE 3
        Mesmo cubo do teste anterior.
        Limite 1 deve encontrar.
    */
    printf("\n===== TESTE 3 =====\n");

    ResultadoBusca teste3 =
        busca_iddfs(&estado, 1);

    mostrar_resultado(&estado, teste3);


    /*
        TESTE 4
        Embaralhamento de 2 movimentos.
        Limite 1 não deve encontrar.
    */
    printf("\n===== TESTE 4 =====\n");

    estado_inicializar(&estado);

    estado_aplicar_movimento(&estado, MOV_DIR);
    estado_aplicar_movimento(&estado, MOV_SUP);

    ResultadoBusca teste4 =
        busca_iddfs(&estado, 1);

    mostrar_resultado(&estado, teste4);


    /*
        TESTE 5
        Mesmo embaralhamento.
        Limite 2 deve encontrar.
    */
    printf("\n===== TESTE 5 =====\n");

    ResultadoBusca teste5 =
        busca_iddfs(&estado, 2);

    mostrar_resultado(&estado, teste5);


    /*
        TESTE 6
        Embaralhamento de 3 movimentos.
        Limite 3 deve encontrar.
    */
    printf("\n===== TESTE 6 =====\n");

    estado_inicializar(&estado);

    estado_aplicar_movimento(&estado, MOV_DIR);
    estado_aplicar_movimento(&estado, MOV_SUP);
    estado_aplicar_movimento(&estado, MOV_FRT);

    ResultadoBusca teste6 =
        busca_iddfs(&estado, 3);

    mostrar_resultado(&estado, teste6);


    return 0;
}