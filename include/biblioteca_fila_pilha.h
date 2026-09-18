#ifndef BIBLIOTECA_FILA_PILHA_H_INCLUDED
#define BIBLIOTECA_FILA_PILHA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "cubo_estado.h"

typedef struct noBusca
{
    EstadoCubo estado;
    MovimentoCubo movimento;
    int profundidade;
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

Pilha* CriaPilha(void)
{
    Pilha *p;
    p = (Pilha*)malloc(sizeof(Pilha));

    if(p==NULL){
        return NULL;
    }

    p->Topo = NULL;
    return p;
}

No* ins_ini(No* t, NoBusca *A)
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

int vaziaPilha(Pilha *p)
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

void Push(Pilha* p, NoBusca *v)
{
    No *novo = ins_ini(p->Topo, v);

    if(novo != NULL){
        p->Topo = novo;
    }
}

No* ret_ini(No* aux)
{
    No* p = aux->prox;
    free(aux);
    return p;
}

NoBusca* Pop(Pilha* p)
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

Pilha* liberaPilha(Pilha* p)
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

void Imprime(Pilha* p)
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

int VaziaFila(Fila* f)
{
    if(f->ini == NULL)
        return 1;

    return 0;
}

Fila* CriaFila()
{
    Fila* f = (Fila*)malloc(sizeof(Fila));

    if(f == NULL){
        return NULL;
    }

    f->ini = f->fim = NULL;
    return f;
}

No* ins_fim(No *fim, NoBusca *A)
{
    No *p = (No*)malloc(sizeof(No));

    p->info = A;
    p->prox = NULL;

    if(fim != NULL)
        fim->prox = p;

    return p;
}

int InsereFila(Fila* f, NoBusca *v)
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

No* retira_ini(No* ini)
{
    No* p = ini->prox;
    free(ini);
    return p;
}

NoBusca* RetiraFila(Fila* f)
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

void imprimeFila(Fila* f)
{
    No* q;

    for(q = f->ini; q != NULL; q = q->prox)
    {
        printf("%p - ", (void*)q->info);
    }

    printf("\n");
}

Fila* liberaFila(Fila* f)
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

#endif
