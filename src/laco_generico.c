#include "laco_generico.h"
#include <stdlib.h>

/*
    elo:
    arrumei o laco generico para evitar que a busca fique analisando varias vezes o mesmo estado do cubo. Antes, todos os 12 sucessores gerados eram adicionados 
    na estrutura sem verificar se aquele estado ja tinha aparecido. Isso fazia com que a busca pudesse voltar para estados anteriores. Por exemplo, fazer DIR 
    e depois DIR_INV faz o cubo voltar para o mesmo estado que estava antes.
*/

/* verifica se o estado que foi gerado ja apareceu antes na busca */
static int estado_ja_visitado(const EstadoCubo *estado, EstadoCubo *visitados, int quantidade)
{
    for (int i = 0; i < quantidade; i++)  /* percorre todos os estados que ja foram guardados */
    {
    
        if (estado_igual(estado, &visitados[i])) /* compara o estado novo com um estado que ja visitamos */
        {
            return 1; 
        }
    }
    return 0; 
}

static int adicionar_visitado(const EstadoCubo *estado, EstadoCubo **visitados, /* guarda um novo estado na lista de estados visitados*/
                              int *quantidade, int *capacidade)
{
    
    if (*quantidade >= *capacidade) /* se o vetor ficar cheio, aumenta o espaco dele */
    {
        *capacidade = *capacidade * 2;

        EstadoCubo *novo = realloc(
            *visitados,
            (*capacidade) * sizeof(EstadoCubo)
        );

        if (novo == NULL) /* se nao conseguiu aumentar o vetor */
        {
            return 0;
        }

        *visitados = novo;
    }

    (*visitados)[*quantidade] = *estado; /* guarda o novo estado no vetor de visitados */
    (*quantidade)++;

    return 1;
}

ResultadoBusca laco_generico(const EstadoCubo *estado_inicial, InterfaceEstrutura *estrutura)
{
    ResultadoBusca resultado; /* variavel pra devolver a funcao ao final */
    resultado.no_final = NULL; /* inicializa as variaveis pois ainda nao inciou o laco */
    resultado.estados_visitados = 0;

    int capacidade_visitados = 100;
    int quantidade_visitados = 0;

    EstadoCubo *visitados = malloc(capacidade_visitados * sizeof(EstadoCubo));

    /* verifica se conseguiu criar o vetor */
    if (visitados == NULL)
    {
        return resultado;
    }

    if (!adicionar_visitado(estado_inicial,&visitados,&quantidade_visitados,&capacidade_visitados)) /*  o estado inicial ja apareceu na busca, entao guardamos ele */
    {
        free(visitados);
        return resultado;
    }

    NoBusca *no_inicial = (NoBusca *)malloc(sizeof(NoBusca)); // aloca memoria para representar o estado de inicio da busca
    
    if (no_inicial == NULL)
    {
        free(visitados);
        return resultado;
    }

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
            free(visitados);
            return resultado;
        }

        // Adicionar estados seguintes na estrutura 
        SucessorCubo sucessores[TOTAL_MOVIMENTOS]; // cria o vetor que vai guardar os 12 sucessores gerados a partir do estado atual
        estado_gerar_sucessores(&atual->estado, sucessores); // chama a funcao sucessora que ja existe, e ela preenche o vetor sucessores

                
    for (int i = 0; i < TOTAL_MOVIMENTOS; i++) /* percorre cada um dos 12 sucessores gerados*/
    {
    
        if (!estado_ja_visitado(&sucessores[i].estado,visitados,quantidade_visitados)) /* verifica se esse estado ainda nao apareceu na busca */
        {
          if (adicionar_visitado(&sucessores[i].estado,&visitados,&quantidade_visitados,&capacidade_visitados)) /* se ainda nao apareceu, guarda ele nos estados visitados */
            {
             NoBusca *filho = (NoBusca *)malloc(sizeof(NoBusca)); /* cria um novo no para representar esse sucessor */

               if (filho != NULL) /* verifica se conseguiu alocar memoria para o novo no */
               {
               filho->estado = sucessores[i].estado;
               filho->movimento = sucessores[i].movimento;
               filho->pai = atual;
               filho->profundidade = atual->profundidade + 1;

              estrutura->inserir(estrutura->estrutura, filho); /* coloca o novo estado na estrutura da busca */
               }
            }
        }
    }

} // fecha o while

    // chegou aqui se a estrutura ficou vazia sem encontrar solucao
    free(visitados);

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