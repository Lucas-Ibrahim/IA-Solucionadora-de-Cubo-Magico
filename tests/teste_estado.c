#include <stdio.h>
#include "../include/cubo_estado.h"

int main(){
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