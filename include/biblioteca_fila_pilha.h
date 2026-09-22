#ifndef BIBLIOTECA_FILA_PILHA_H_INCLUDED
#define BIBLIOTECA_FILA_PILHA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "cubo_estado.h"

/* 
   Comentario do Lucas: deixei todas as funcoes como static aqui.
   Isso porque quando mais de um arquivo .c inclui esse header no
   mesmo programa, o corpo de cada funcao (que ta escrito aqui dentro
   do .h) fica duplicado, e o linker da erro de funcao definida duas
   vezes. Colocando static, cada funcao passa a valer so dentro do
   arquivo que incluiu o header, entao para de dar esse erro. 
*/

typedef struct noBusca
{
    EstadoCubo estado;
    MovimentoCubo movimento;
    
    int profundidade;

    int f;
    
    struct noBusca *pai;
} NoBusca;

typedef struct no
{
    NoBusca *info;
    struct no *prox;
} No;

typedef struct Pilha
{
    No *Topo;
} Pilha;

static Pilha* CriaPilha(void)
{
    Pilha *p;
    p = (Pilha*)malloc(sizeof(Pilha));

    if(p==NULL){
        return NULL;
    }

    p->Topo = NULL;
    return p;
}

static No* ins_ini(No* t, NoBusca *A)
{
    No* aux = (No*)malloc(sizeof(No));
    //verifica se alocou espaço
    if(aux == NULL){
        return NULL;
    }
    aux->info = A;
    aux->prox = t;
    return aux;
}

static int vaziaPilha(Pilha *p)
{
    if(p->Topo == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static void Push(Pilha* p, NoBusca *v)
{
    No *novo = ins_ini(p->Topo, v);

    if(novo != NULL){
        p->Topo = novo;
    }
}

static No* ret_ini(No* aux)
{
    No* p = aux->prox;
    free(aux);
    return p;
}

static NoBusca* Pop(Pilha* p)
{
    NoBusca *v;

    if(vaziaPilha(p) == 1)
    {
        printf("A Pilha esta Vazia");
        exit(1);
    }

    v = p->Topo->info;
    p->Topo = ret_ini(p->Topo);

    return v;
}

static Pilha* liberaPilha(Pilha* p)
{
    No* aux;
    aux = p->Topo;

    while(p->Topo != NULL)
    {
        p->Topo = p->Topo->prox;
        free(aux);
        aux = p->Topo;
    }

    free(p);
    return NULL;
}

static void Imprime(Pilha* p)
{
    if(vaziaPilha(p) == 1)
    {
        printf("A Pilha esta Vazia");
        return;
    }

    No* aux = p->Topo;

    while(aux != NULL)
    {
        printf("%p - ", (void*)aux->info);
        aux = aux->prox;
    }

    printf("\n");
}


typedef struct fila
{
    No *ini;
    No *fim;
} Fila;

static int VaziaFila(Fila* f)
{
    if(f->ini == NULL)
        return 1;

    return 0;
}

static Fila* CriaFila()
{
    Fila* f = (Fila*)malloc(sizeof(Fila));

    if(f == NULL){
        return NULL;
    }

    f->ini = f->fim = NULL;
    return f;
}

static No* ins_fim(No *fim, NoBusca *A)
{
    No *p = (No*)malloc(sizeof(No));

    p->info = A;
    p->prox = NULL;

    if(fim != NULL)
        fim->prox = p;

    return p;
}

static int InsereFila(Fila* f, NoBusca *v)
{
    No *novo = ins_fim(f->fim, v);

    if(novo == NULL){
        return 0;
    }

    f->fim = novo;

    if(f->ini == NULL){
        f->ini = f->fim;
    }

    return 1;
}

static No* retira_ini(No* ini)
{
    No* p = ini->prox;
    free(ini);
    return p;
}

static NoBusca* RetiraFila(Fila* f)
{
    NoBusca *v;

    if(VaziaFila(f))
    {
        printf("Fila vazia.\n");
        return NULL;
    }

    v = f->ini->info;
    f->ini = retira_ini(f->ini);

    if(f->ini == NULL)
    {
        f->fim = NULL;
    }

    return v;
}

static void imprimeFila(Fila* f)
{
    No* q;

    for(q = f->ini; q != NULL; q = q->prox)
    {
        printf("%p - ", (void*)q->info);
    }

    printf("\n");
}

static Fila* liberaFila(Fila* f)
{
    No* q = f->ini;

    while(q != NULL)
    {
        No* t = q->prox;
        free(q);
        q = t;
    }

    free(f);
    return NULL;
}

typedef struct prioridade
{
    No *ini;
} FilaPrioridade;

static FilaPrioridade *CriaFilaPrioridade()
{
    FilaPrioridade *f =
        (FilaPrioridade*)malloc(sizeof(FilaPrioridade));

    if(f == NULL)
        return NULL;

    f->ini = NULL;

    return f;
}

static int VaziaFilaPrioridade(FilaPrioridade *f)
{
    return f->ini == NULL;
}

static void InserirPrioridade(
    FilaPrioridade *f,
    NoBusca *novo)
{
    No *n = (No*)malloc(sizeof(No));

    n->info = novo;
    n->prox = NULL;

    if(f->ini == NULL)
    {
        f->ini = n;
        return;
    }

    if(novo->f < f->ini->info->f)
    {
        n->prox = f->ini;
        f->ini = n;
        return;
    }

    No *atual = f->ini;

    while(atual->prox != NULL &&
          atual->prox->info->f <= novo->f)
    {
        atual = atual->prox;
    }

    n->prox = atual->prox;
    atual->prox = n;
}

static NoBusca *RetirarPrioridade(
    FilaPrioridade *f)
{
    if(f->ini == NULL)
        return NULL;

    No *aux = f->ini;

    NoBusca *retorno = aux->info;

    f->ini = aux->prox;

    free(aux);

    return retorno;
}

static FilaPrioridade *
LiberaFilaPrioridade(FilaPrioridade *f)
{
    No *atual = f->ini;

    while(atual != NULL)
    {
        No *prox = atual->prox;

        free(atual);

        atual = prox;
    }

    free(f);

    return NULL;
}

#endif
