#ifndef BUSCA_IDDFS_H
#define BUSCA_IDDFS_H

#include "cubo_estado.h"

typedef struct {
    EstadoCubo *estados;
    MovimentoCubo *movimentos; 
    int tamanho;
    int capacidade;
} CaminhoIDDFS;

//verifica se o estado já está no caminho para evitar ciclos
int caminho_contem_estado(const CaminhoIDDFS *caminho, const EstadoCubo *estado); 

//adciona sucessor ao caminho
int caminho_adicionar(CaminhoIDDFS *caminho, const EstadoCubo *estado, MovimentoCubo movimento);

void caminho_remover(CaminhoIDDFS *caminho);

int caminho_inicializar(CaminhoIDDFS *caminho, const EstadoCubo *estado, int capacidade);

void caminho_liberar(CaminhoIDDFS *caminho);

int busca_iddfs(const EstadoCubo *estado_inicial, int limite_maximo, CaminhoIDDFS *solucao, unsigned long *estados_visitados);


#endif