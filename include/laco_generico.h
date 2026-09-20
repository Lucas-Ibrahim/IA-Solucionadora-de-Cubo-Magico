#ifndef LACO_GENERICO_H
#define LACO_GENERICO_H

#include "biblioteca_fila_pilha.h"

typedef struct 
{    
    void *estrutura; // guardar qual tipo de estrutura de dados estamos usando (fila, pilha, fila de prioridade)
    void (*inserir)(void *estrutura, NoBusca *no); // guardar o endenreco de uma funcao e inserir o noBusca
    NoBusca *(*remover)(void *estrutura); // guardar o endereco de uma funcao e remover o noBusca
    int (*vazia)(void *estrutura); // retorna 1 para vazia, 0 para nao vazia

}InterfaceEstrutura; // essa estrutura vai servir pra gente deixar ela universal, entao independentemente se for fila, pilha ou outra o laco generico vai funcionar de forma igual pra todas sem oprecisar adaptar ele

typedef struct {
    NoBusca *no_final; // guarda o no onde a busca terminou
    int estados_visitados; // conta quantos estados foram visitados
} ResultadoBusca;

ResultadoBusca laco_generico(const EstadoCubo *estado_inicial, InterfaceEstrutura *estrutura); // declarando a funcao do laco generico

int busca_reconstruir_caminho(NoBusca *no_final, MovimentoCubo *saida, int capacidade); // funcao que quando o algoritmo acha o camiho da solucao, ela guarda todos os movimentos pra gente conseguir mostrar a solucao com o cubo mexendo



#endif