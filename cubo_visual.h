#ifndef CUBO_VISUAL_H
#define CUBO_VISUAL_H

#include "cubo_estado.h"

#ifdef __cplusplus
extern "C" {
#endif

void abrir_jogo_manual(void);

void abrir_visualizacao_solucao(MovimentoCubo *embaralhamento, int quantidade_embaralhamento, MovimentoCubo *solucao, int quantidade_solucao);

#ifdef __cplusplus
}
#endif

#endif