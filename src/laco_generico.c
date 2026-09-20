#include "laco_generico.h"
#include <stdlib.h>

ResultadoBusca laco_generico(const EstadoCubo *estado_inicial, InterfaceEstrutura *estrutura)
{
    ResultadoBusca resultado; // variavel pra devolver a funcao ao fina;
    
    resultado.no_final = NULL; // inicializa as variaveis pois ainda nao inciou o laco
    resultado.estados_visitados = 0;

    NoBusca *no_inicial = (NoBusca *)malloc(sizeof(NoBusca)); // aloca memoria para representar o estado de inicio da busca
    
    no_inicial->estado = *estado_inicial; // estado de inicio pega o parametro que enviamos para iniciar a busca
    no_inicial->pai = NULL; // nao tem "pai" o inicio
    no_inicial->profundidade = 0; // ainda nao fizemos movimentos entao comeca zerado

    // Adicionar estado na estrutura 
    estrutura->inserir(estrutura->estrutura, no_inicial);

    // Enquanto a estrutura nao estiver vazia ficamos no laco, por isso o while
    while (!estrutura->vazia(estrutura->estrutura)) 
    {
        // Remover proximo estado da estrutura
        NoBusca *atual = estrutura->remover(estrutura->estrutura);
        resultado.estados_visitados++;

        // Avaliar estado 
        if (estado_resolvido(&atual->estado)) 
        {
            // Se estado final -> mostrar solucao e encerrar
            resultado.no_final = atual;
            return resultado;
        }

        // Adicionar estados seguintes na estrutura 
        SucessorCubo sucessores[TOTAL_MOVIMENTOS]; // cria o vetor que vai guardar os 12 sucessores gerados a partir do estado atual
        estado_gerar_sucessores(&atual->estado, sucessores); // chama a funcao sucessora que ja existe, e ela preenche o vetor sucessores

        for (int i = 0; i < TOTAL_MOVIMENTOS; i++) // percorre cada um dos 12 sucessores gerados, um de cada vez
        { 
            NoBusca *filho = (NoBusca *)malloc(sizeof(NoBusca)); // aloca um novo no pra representar esse sucessor
            
            // insere todas informacoes para o novo nó (o prox sucessor)
            filho->estado = sucessores[i].estado;
            filho->movimento = sucessores[i].movimento;
            filho->pai = atual;
            filho->profundidade = atual->profundidade + 1;

            estrutura->inserir(estrutura->estrutura, filho);
        }
    }

    return resultado;
}


int busca_reconstruir_caminho(NoBusca *no_final, MovimentoCubo *saida, int capacidade) {
    
    // primeira passada: so conta quantos movimentos existem, subindo ate a raiz
    int quantidade = 0;
    NoBusca *atual = no_final;
    while (atual != NULL && atual->pai != NULL) {
        quantidade++;
        atual = atual->pai;
    }

    // segunda passada: preenche o vetor de tras pra frente
    // assim o primeiro movimento da solucao fica no indice 0, sem precisar inverter nada depois
    int indice = quantidade - 1;
    atual = no_final;
    while (atual != NULL && atual->pai != NULL && indice >= 0) {
        if (indice < capacidade) {
            saida[indice] = atual->movimento;
        }
        indice--;
        atual = atual->pai;
    }

    return quantidade;
}