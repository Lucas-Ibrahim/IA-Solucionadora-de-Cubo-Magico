#include <stdio.h>
#include <assert.h>
#include "../include/cubo_estado.h"

int main(){
    MovimentoCubo primeira[4], repetida[4], diferente[4];
    estado_gerar_embaralhamento(42, primeira, 4);
    estado_gerar_embaralhamento(42, repetida, 4);
    estado_gerar_embaralhamento(43, diferente, 4);
    int mudou = 0;
    for (int i = 0; i < 4; i++) {
        assert(primeira[i] == repetida[i]);
        assert(primeira[i] >= 0 && primeira[i] < TOTAL_MOVIMENTOS);
        if (primeira[i] != diferente[i]) mudou = 1;
    }
    assert(mudou);

    EstadoCubo estado;

    estado_inicializar(&estado);
    
    estado_mov_dir(&estado);
    estado_mov_sup(&estado);



    printf("Pecas: ");
    for(int i = 0; i < 8; i++){
        printf("%d ", estado.pecas[i]);
    }

    printf("\nOrientacao: ");
    for(int i = 0; i < 8; i++){
        printf("%d ", estado.orientacao[i]);
    }
    
    printf("\nResolvido: %d\n", estado_resolvido(&estado));

    printf("\n");

    return 0;
}
