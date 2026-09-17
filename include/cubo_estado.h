#ifndef CUBO_ESTADO_H
#define CUBO_ESTADO_H

typedef struct {
    unsigned char pecas [8];
    unsigned char orientacao [8];
} EstadoCubo;

typedef enum {
    MOV_DIR,
    MOV_DIR_INV,

    MOV_ESQ,
    MOV_ESQ_INV,

    MOV_SUP,
    MOV_SUP_INV,

    MOV_INF,
    MOV_INF_INV,

    MOV_FRT,
    MOV_FRT_INV,

    MOV_TRS,
    MOV_TRS_INV
} MovimentoCubo; 

#define TOTAL_MOVIMENTOS 12

typedef struct {
    EstadoCubo estado;
    MovimentoCubo movimento;
} SucessorCubo;

void estado_inicializar(EstadoCubo *estado);

int estado_resolvido(const EstadoCubo *estado); //Função Avaliadora

void estado_mov_dir(EstadoCubo *estado);
void estado_mov_dir_inv(EstadoCubo *estado);

void estado_mov_esq(EstadoCubo *estado);
void estado_mov_esq_inv(EstadoCubo *estado);

void estado_mov_sup(EstadoCubo *estado);
void estado_mov_sup_inv(EstadoCubo *estado);

void estado_mov_inf(EstadoCubo *estado);
void estado_mov_inf_inv(EstadoCubo *estado);

void estado_mov_frt(EstadoCubo *estado);
void estado_mov_frt_inv(EstadoCubo *estado);

void estado_mov_trs(EstadoCubo *estado);
void estado_mov_trs_inv(EstadoCubo *estado);

void estado_aplicar_movimento(EstadoCubo *estado, MovimentoCubo movimento);

int estado_igual(const EstadoCubo *a, const EstadoCubo *b);

void estado_gerar_sucessores(const EstadoCubo *estado, SucessorCubo sucessores[TOTAL_MOVIMENTOS]);

#endif