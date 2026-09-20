#include "busca_bfs.h"
#include "biblioteca_fila_pilha.h"
#include <stdio.h>

static void bfs_inserir(void *estrutura, NoBusca *no) /* função que insere um no na fila*/
{
    Fila *fila = (Fila*)estrutura;
    InsereFila(fila,no);
}

static NoBusca *bfs_remover(void *estrutura) /* função que remove o prox no da fila*/
{
    Fila *fila = (Fila*)estrutura;
    return RetiraFila(fila);
}

static int bfs_vazia(void *estrutura) /* função para ver se a fila esta vazia*/
{
    Fila *fila = (Fila*)estrutura;
    return VaziaFila(fila);
}

ResultadoBusca busca_bfs(const EstadoCubo *estado_inicial)
{
    /* cria a fila que vai ser usada pela busca em largura */
    Fila *fila = CriaFila();

    /* configura o laco generico para usar as funcoes da fila */
    InterfaceEstrutura estrutura;

    estrutura.estrutura = fila;
    estrutura.inserir = bfs_inserir;
    estrutura.remover = bfs_remover;
    estrutura.vazia = bfs_vazia;

    ResultadoBusca resultado = laco_generico(estado_inicial, &estrutura);

    liberaFila(fila);

    return resultado;


}