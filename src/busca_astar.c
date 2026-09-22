#include "busca_astar.h"
#include "biblioteca_fila_pilha.h"

static int heuristica(const EstadoCubo *estado)
{
    int errado = 0;
   
    for (int i = 0; i < 8; i++)
    {
        if (estado->pecas[i] != i || estado->orientacao[i] != 0)
            errado++;
    }
   
    return (errado + 3) / 4;
}

static void astar_inserir(
    void *estrutura,
    NoBusca *no)
{
    FilaPrioridade *fila =
        (FilaPrioridade*)estrutura;

    no->f =
        no->profundidade +
        heuristica(&no->estado);

    InserirPrioridade(fila,no);
}
static NoBusca *astar_remover(
    void *estrutura)
{
    FilaPrioridade *fila =
        (FilaPrioridade*)estrutura;

    return RetirarPrioridade(fila);
}

static int astar_vazia(
    void *estrutura)
{
    FilaPrioridade *fila =
        (FilaPrioridade*)estrutura;

    return VaziaFilaPrioridade(fila);
}

ResultadoBusca busca_astar(
    const EstadoCubo *estado_inicial)
{
    FilaPrioridade *fila =
        CriaFilaPrioridade();

    InterfaceEstrutura estrutura;

    estrutura.estrutura = fila;

    estrutura.inserir = astar_inserir;

    estrutura.remover = astar_remover;

    estrutura.vazia = astar_vazia;

    ResultadoBusca resultado =
        laco_generico(
            estado_inicial,
            &estrutura);

    LiberaFilaPrioridade(fila);

    return resultado;
}