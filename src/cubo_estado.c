#include "../include/cubo_estado.h"

void estado_inicializar(EstadoCubo *estado){

    for(int i = 0; i < 8; i++){
        estado->pecas[i] = i;
        estado->orientacao[i] = 0;
    }
}

int estado_resolvido(const EstadoCubo *estado){
    for(int i = 0; i < 8; i++){
        if(estado->pecas[i] != i || estado->orientacao[i] != 0){ // posição incorreta ou orientação incorreta
            return 0; // Não resolvido
        }
    }
    return 1; // Resolvido
}

void estado_mov_dir(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[4] = anterior.pecas[0];
    estado->pecas[7] = anterior.pecas[4];
    estado->pecas[3] = anterior.pecas[7];
    estado->pecas[0] = anterior.pecas[3];

    estado->orientacao[4] = (anterior.orientacao[0] + 1) % 3;
    estado->orientacao[7] = (anterior.orientacao[4] + 2) % 3;
    estado->orientacao[3] = (anterior.orientacao[7] + 1) % 3;
    estado->orientacao[0] = (anterior.orientacao[3] + 2) % 3;
}

void estado_mov_dir_inv(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[0] = anterior.pecas[4];
    estado->pecas[4] = anterior.pecas[7];
    estado->pecas[7] = anterior.pecas[3];
    estado->pecas[3] = anterior.pecas[0];
    
    estado->orientacao[0] = (anterior.orientacao[4] + 2) % 3;
    estado->orientacao[4] = (anterior.orientacao[7] + 1) % 3;
    estado->orientacao[7] = (anterior.orientacao[3] + 2) % 3;
    estado->orientacao[3] = (anterior.orientacao[0] + 1) % 3;
}

void estado_mov_esq(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[1] = anterior.pecas[5];
    estado->pecas[5] = anterior.pecas[6];
    estado->pecas[6] = anterior.pecas[2];
    estado->pecas[2] = anterior.pecas[1];

    estado->orientacao[1] = (anterior.orientacao[5] + 1) % 3;
    estado->orientacao[5] = (anterior.orientacao[6] + 2) % 3;
    estado->orientacao[6] = (anterior.orientacao[2] + 1) % 3;
    estado->orientacao[2] = (anterior.orientacao[1] + 2) % 3;
}

void estado_mov_esq_inv(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[5] = anterior.pecas[1];
    estado->pecas[6] = anterior.pecas[5];
    estado->pecas[2] = anterior.pecas[6];
    estado->pecas[1] = anterior.pecas[2];

    estado->orientacao[5] = (anterior.orientacao[1] + 2) % 3;
    estado->orientacao[6] = (anterior.orientacao[5] + 1) % 3;
    estado->orientacao[2] = (anterior.orientacao[6] + 2) % 3;
    estado->orientacao[1] = (anterior.orientacao[2] + 1) % 3;
}

void estado_mov_sup(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[5] = anterior.pecas[1];
    estado->pecas[4] = anterior.pecas[5];
    estado->pecas[0] = anterior.pecas[4];
    estado->pecas[1] = anterior.pecas[0];

    estado->orientacao[5] = anterior.orientacao[1];
    estado->orientacao[4] = anterior.orientacao[5];
    estado->orientacao[0] = anterior.orientacao[4];
    estado->orientacao[1] = anterior.orientacao[0];

}

void estado_mov_sup_inv(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[1] = anterior.pecas[5];
    estado->pecas[5] = anterior.pecas[4];
    estado->pecas[4] = anterior.pecas[0];  
    estado->pecas[0] = anterior.pecas[1];

    estado->orientacao[1] = anterior.orientacao[5];
    estado->orientacao[5] = anterior.orientacao[4];
    estado->orientacao[4] = anterior.orientacao[0];
    estado->orientacao[0] = anterior.orientacao[1];

}

void estado_mov_inf(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[2] = anterior.pecas[6];
    estado->pecas[6] = anterior.pecas[7];
    estado->pecas[7] = anterior.pecas[3];
    estado->pecas[3] = anterior.pecas[2];

    estado->orientacao[2] = anterior.orientacao[6];
    estado->orientacao[6] = anterior.orientacao[7];
    estado->orientacao[7] = anterior.orientacao[3];
    estado->orientacao[3] = anterior.orientacao[2];
}

void estado_mov_inf_inv(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[6] = anterior.pecas[2];
    estado->pecas[7] = anterior.pecas[6];
    estado->pecas[3] = anterior.pecas[7];
    estado->pecas[2] = anterior.pecas[3];

    estado->orientacao[6] = anterior.orientacao[2];
    estado->orientacao[7] = anterior.orientacao[6];
    estado->orientacao[3] = anterior.orientacao[7];
    estado->orientacao[2] = anterior.orientacao[3];

}

void estado_mov_frt(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[0] = anterior.pecas[1];
    estado->pecas[1] = anterior.pecas[2];
    estado->pecas[2] = anterior.pecas[3];
    estado->pecas[3] = anterior.pecas[0];

    estado->orientacao[0] = (anterior.orientacao[1] + 1) % 3;
    estado->orientacao[1] = (anterior.orientacao[2] + 2) % 3;
    estado->orientacao[2] = (anterior.orientacao[3] + 1) % 3;
    estado->orientacao[3] = (anterior.orientacao[0] + 2) % 3;
}

void estado_mov_frt_inv(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[1] = anterior.pecas[0];
    estado->pecas[2] = anterior.pecas[1];
    estado->pecas[3] = anterior.pecas[2];
    estado->pecas[0] = anterior.pecas[3];

    estado->orientacao[1] = (anterior.orientacao[0] + 2) % 3;
    estado->orientacao[2] = (anterior.orientacao[1] + 1) % 3;
    estado->orientacao[3] = (anterior.orientacao[2] + 2) % 3;
    estado->orientacao[0] = (anterior.orientacao[3] + 1) % 3;
}

void estado_mov_trs(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[5] = anterior.pecas[4];
    estado->pecas[6] = anterior.pecas[5];
    estado->pecas[7] = anterior.pecas[6];
    estado->pecas[4] = anterior.pecas[7];

    estado->orientacao[5] = (anterior.orientacao[4] + 1) % 3;
    estado->orientacao[6] = (anterior.orientacao[5] + 2) % 3;
    estado->orientacao[7] = (anterior.orientacao[6] + 1) % 3;
    estado->orientacao[4] = (anterior.orientacao[7] + 2) % 3;
}

void estado_mov_trs_inv(EstadoCubo *estado){
    EstadoCubo anterior = *estado;

    estado->pecas[4] = anterior.pecas[5];
    estado->pecas[5] = anterior.pecas[6];
    estado->pecas[6] = anterior.pecas[7];
    estado->pecas[7] = anterior.pecas[4];

    estado->orientacao[4] = (anterior.orientacao[5] + 2) % 3;
    estado->orientacao[5] = (anterior.orientacao[6] + 1) % 3;
    estado->orientacao[6] = (anterior.orientacao[7] + 2) % 3;
    estado->orientacao[7] = (anterior.orientacao[4] + 1) % 3;
}

void estado_aplicar_movimento(EstadoCubo *estado, MovimentoCubo movimento){
    switch(movimento){
        case MOV_DIR:
            estado_mov_dir(estado);
            break;
        case MOV_DIR_INV:
            estado_mov_dir_inv(estado);
            break;
        case MOV_ESQ:
            estado_mov_esq(estado);
            break;
        case MOV_ESQ_INV:
            estado_mov_esq_inv(estado);
            break;
        case MOV_SUP:
            estado_mov_sup(estado);
            break;
        case MOV_SUP_INV:
            estado_mov_sup_inv(estado);
            break;
        case MOV_INF:
            estado_mov_inf(estado);
            break;
        case MOV_INF_INV:
            estado_mov_inf_inv(estado);
            break;
        case MOV_FRT:
            estado_mov_frt(estado);
            break;
        case MOV_FRT_INV:
            estado_mov_frt_inv(estado);
            break;
        case MOV_TRS:
            estado_mov_trs(estado);
            break;
        case MOV_TRS_INV:
            estado_mov_trs_inv(estado);
            break;
    }
}

int estado_igual(const EstadoCubo *a, const EstadoCubo *b){
    for(int i = 0; i < 8; i++){
        if(a->pecas[i] != b->pecas[i] || a->orientacao[i] != b->orientacao[i]){
            return 0; // Não são iguais
        }
    }
    return 1; // São iguais
}

static const MovimentoCubo movimentos[TOTAL_MOVIMENTOS] = {
    MOV_DIR, MOV_DIR_INV,
    MOV_ESQ, MOV_ESQ_INV,
    MOV_SUP, MOV_SUP_INV,
    MOV_INF, MOV_INF_INV,
    MOV_FRT, MOV_FRT_INV,
    MOV_TRS, MOV_TRS_INV
};

//Função Sucessora: Gera todos os sucessores de um estado do cubo
void estado_gerar_sucessores(const EstadoCubo *estado, SucessorCubo sucessores[TOTAL_MOVIMENTOS]){
    
    for(int i = 0; i < TOTAL_MOVIMENTOS; i++){
        sucessores[i].estado = *estado; // Copia o estado atual
        sucessores[i].movimento = movimentos[i]; // Define o movimento correspondente

        estado_aplicar_movimento(&sucessores[i].estado, movimentos[i]); // Aplica o movimento
    }
}


