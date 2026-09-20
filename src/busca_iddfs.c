#include <stdlib.h>
#include "../include/busca_iddfs.h"

#include "busca_iddfs.h"
#include "biblioteca_fila_pilha.h"

// Estrutura IDDFS.
typedef struct {
    Pilha *pilha;   // Guarda a pilha  
    int limite;     // Guarda limite de profundidade atual
} EstruturaIDDFS;


// Adapta a função de inserção para o formato esperado pelo laço genérico
// O nó só entra na pilha se estiver dentro do limite de profundidade atual
static void iddfs_inserir(void *estrutura, NoBusca *no){

    EstruturaIDDFS *iddfs = (EstruturaIDDFS *)estrutura;

    if(no->profundidade <= iddfs->limite){
        Push(iddfs->pilha, no);
    }
}


// Adapta a remoção da pilha
static NoBusca *iddfs_remover(void *estrutura){

    EstruturaIDDFS *iddfs = (EstruturaIDDFS *)estrutura;

    return Pop(iddfs->pilha);
}


static int iddfs_vazia(void *estrutura){

    EstruturaIDDFS *iddfs = (EstruturaIDDFS *)estrutura;

    return vaziaPilha(iddfs->pilha);
}


// Executa a busca em profundidade limitada iterativa
// A busca é repetida várias vezes, aumentando o limite de profundidade
ResultadoBusca busca_iddfs(
    const EstadoCubo *estado_inicial,
    int limite_maximo
)
{
    ResultadoBusca resultado;

    // Inicialmente nenhuma solução foi encontrada
    resultado.no_final = NULL;
    resultado.estados_visitados = 0;

    // IDDFS: começa no limite 0 e aumenta até limite_maximo
    for(int limite = 0; limite <= limite_maximo; limite++){
        // Cada nova profundidade utiliza uma nova pilha.
        Pilha *pilha = CriaPilha();

        if(pilha == NULL){
            return resultado;
        }

        // Associa a pilha ao limite da iteração atual
        EstruturaIDDFS iddfs;

        iddfs.pilha = pilha;
        iddfs.limite = limite;

        // Configura a interface usada pelo laço genérico
        InterfaceEstrutura estrutura;

        estrutura.estrutura = &iddfs;
        estrutura.inserir = iddfs_inserir;
        estrutura.remover = iddfs_remover;
        estrutura.vazia = iddfs_vazia;

        // Executa o mesmo laço genérico usado pelas outras buscas
        ResultadoBusca tentativa = laco_generico(estado_inicial, &estrutura);

        // Como o IDDFS repete os níveis anteriores, salva os estados em todas as tentativas
        resultado.estados_visitados += tentativa.estados_visitados;

        // Libera a pilha depois da tentativa
        liberaPilha(pilha);

        // Se encontrou solução nesse limite, encerra a IDDFS
        if(tentativa.no_final != NULL){

            resultado.no_final =
                tentativa.no_final;

            return resultado;
        }
    }

    // Nenhuma solução encontrada
    return resultado;
}