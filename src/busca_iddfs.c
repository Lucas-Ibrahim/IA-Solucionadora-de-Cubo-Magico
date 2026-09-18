#include <stdlib.h>
#include "../include/busca_iddfs.h"

int caminho_contem_estado(const CaminhoIDDFS *caminho, const EstadoCubo *estado){
    
    for(int i = 0; i <= caminho->tamanho; i++){
        if(estado_igual(&caminho->estados[i], estado)){
            return 1; // Estado encontrado no caminho
        }
    }
    return 0; // Estado não encontrado no caminho
}

int caminho_adicionar(CaminhoIDDFS *caminho, const EstadoCubo *estado, MovimentoCubo movimento){
    
    if(caminho->tamanho >= caminho->capacidade){
        return 0;
    }

    caminho->movimentos[caminho->tamanho] = movimento;
    caminho->estados[caminho->tamanho + 1] = *estado;

    caminho->tamanho++;

    return 1;
}

void caminho_remover(CaminhoIDDFS *caminho){

    if(caminho->tamanho > 0){
        caminho->tamanho--;
    }
}

int caminho_inicializar(CaminhoIDDFS *caminho, const EstadoCubo *estado, int capacidade){
    
    if(capacidade < 0){
        return 0;
    }

    caminho->estados = malloc((capacidade + 1) * sizeof(EstadoCubo));

    //evita malloc(0)
    if(capacidade > 0){
        caminho->movimentos = malloc(capacidade * sizeof(MovimentoCubo));
    }else{
        caminho->movimentos = NULL;
    }
    

    // Falha se não alocar estados ou, quando necessário(capacidade = 0), não alocar movimentos, se capacidade>0 verifica falha ao alocar movimentos
    if(caminho->estados == NULL || (capacidade > 0 && caminho->movimentos == NULL)){

        free(caminho->estados);
        free(caminho->movimentos);

        return 0;
    }

    caminho->estados[0] = *estado;

    caminho->tamanho = 0;

    caminho->capacidade = capacidade;

    return 1;
}

void caminho_liberar(CaminhoIDDFS *caminho){

    free(caminho->estados);
    free(caminho->movimentos);

    caminho->estados = NULL;
    caminho->movimentos = NULL;
    
    caminho->tamanho = 0;
    caminho->capacidade = 0;
}

static int busca_limitada(CaminhoIDDFS *caminho, int limite, unsigned long *estados_visitados){
    
    EstadoCubo *estado_atual = &caminho->estados[caminho->tamanho];

    (*estados_visitados)++; // quantidade de etados visitados

    //função avaliadora
    if(estado_resolvido(estado_atual)){
        return 1;
    }

    //chegou à profundidade máxima
    if(caminho->tamanho >= limite){
        return 0;
    }

    SucessorCubo sucessores[TOTAL_MOVIMENTOS];

    //função sucessora
    estado_gerar_sucessores(estado_atual, sucessores);

    for(int i=0; i < TOTAL_MOVIMENTOS; i++){
        //evita voltar para um estado que ja esta no caminho
        if(caminho_contem_estado(caminho, &sucessores[i].estado)){
            continue;
        }

        if(!caminho_adicionar(caminho, &sucessores[i].estado, sucessores[i].movimento)){
            continue;
        }

        //aprofunda a busca (recursão)
        if(busca_limitada(caminho, limite, estados_visitados)){
            return 1;
        }

        //Não encontrou nesse ramo, volta para estado anterior
        caminho_remover(caminho);
    }
    return 0;
}

int busca_iddfs(const EstadoCubo *estado_inicial, int limite_maximo, CaminhoIDDFS *solucao, unsigned long *estados_visitados){

    *estados_visitados = 0;

    solucao->estados = NULL;
    solucao->movimentos = NULL;
    solucao->tamanho = 0;
    solucao->capacidade = 0;

    for(int limite = 0; limite <= limite_maximo; limite++){

        CaminhoIDDFS caminho;

        if(!caminho_inicializar(&caminho, estado_inicial, limite)){
            return 0;
        }

        if(busca_limitada(&caminho, limite, estados_visitados)){
            *solucao = caminho;
            //lembrar de, quando usar a solucao, liberar caminho 
            return 1;
        }

        caminho_liberar(&caminho);
    }
    return 0;
}