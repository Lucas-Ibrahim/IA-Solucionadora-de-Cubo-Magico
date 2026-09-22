#include "laco_generico.h"
#include <stdlib.h>

/*
    elo:
    arrumei o laco generico para evitar que a busca fique analisando varias vezes o mesmo estado do cubo. Antes, todos os 12 sucessores gerados eram adicionados 
    na estrutura sem verificar se aquele estado ja tinha aparecido. Isso fazia com que a busca pudesse voltar para estados anteriores. Por exemplo, fazer DIR 
    e depois DIR_INV faz o cubo voltar para o mesmo estado que estava antes.
*/

//Pedro: Para IDDFS, precciso saber em qual profundidade aquele estado foi visitado, para evitar problema de dois estados iguais em profundidades diferentes, onde um estado fica como ja visitado por causa de outro estado
//Ex:   estado X encontrado na profundidade 4 → rejeitado pelo limite
//      estado X aparece depois na profundidade 2 → bloqueado como "já visitado" (isso nao deve acontecer)
typedef struct 
{
    EstadoCubo estado;
    int profundidade;
} EstadoVisitado;

//Pedro: Troquei EstadoCubo *visitados por EstadoVisitado *visitados, e suas reações em cadeia

static ListaNos *registrar_no(ListaNos *lista, NoBusca *no)
{
    ListaNos *novo = malloc(sizeof(ListaNos));

    if (novo == NULL) 
    {
        return lista; // se falhar aqui, so nao rastreia esse (nao trava o programa)
    }
   
    novo->no = no;
    novo->prox = lista;
    return novo;
}

/* verifica se o estado que foi gerado ja apareceu antes na busca */
static int estado_ja_visitado(const EstadoCubo *estado, EstadoVisitado *visitados, int quantidade)
{
    for (int i = 0; i < quantidade; i++)  /* percorre todos os estados que ja foram guardados */
    {
    
        if (estado_igual(estado, &visitados[i].estado)) /* compara o estado novo com um estado que ja visitamos */
        {
            return i; 
        }
    }
    return -1; 
}

static int adicionar_visitado(const EstadoCubo *estado, int profundidade, EstadoVisitado **visitados, /* guarda um novo estado na lista de estados visitados*/
                              int *quantidade, int *capacidade)
{
    
    if (*quantidade >= *capacidade) /* se o vetor ficar cheio, aumenta o espaco dele */
    {
        *capacidade = *capacidade * 2;

        EstadoVisitado *novo = realloc(
            *visitados,
            (*capacidade) * sizeof(EstadoVisitado)
        );

        if (novo == NULL) /* se nao conseguiu aumentar o vetor */
        {
            return 0;
        }

        *visitados = novo;
    }

    (*visitados)[*quantidade].estado = *estado; /* guarda o novo estado no vetor de visitados */
    (*visitados)[*quantidade].profundidade = profundidade; // guarda profundidade do estado salvo
    (*quantidade)++;

    return 1;
}

static int deve_explorar (const EstadoCubo *estado, int profundidade, EstadoVisitado **visitados, int *quantidade, int *capacidade){
    
    int indice = estado_ja_visitado(estado, *visitados, *quantidade);

    if (indice == -1){      //estado X nunca foi visitado (pode_explorar)
        return adicionar_visitado(estado, profundidade, visitados, quantidade, capacidade);
    }

    //estado X já foi visitado, mas agora profundidade do estado é menor, portanto atualiza e permite explorar
    if (profundidade < (*visitados)[indice].profundidade){      

        (*visitados)[indice].profundidade = profundidade;
        return 1;
    }
    return 0;   //estado X foi visitado e profundidade atual é maior que anterior (não eplorar)
}

ResultadoBusca laco_generico(const EstadoCubo *estado_inicial, InterfaceEstrutura *estrutura)
{
    ResultadoBusca resultado; /* variavel pra devolver a funcao ao final */
    resultado.no_final = NULL; /* inicializa as variaveis pois ainda nao inciou o laco */
    resultado.todos_nos = NULL; 
    resultado.estados_visitados = 0;

    int capacidade_visitados = 100;
    int quantidade_visitados = 0;

    EstadoVisitado *visitados = malloc(capacidade_visitados * sizeof(EstadoVisitado));
     ListaNos *todos = NULL;

    /* verifica se conseguiu criar o vetor */
    if (visitados == NULL)
    {
        return resultado;
    }

    if (!adicionar_visitado(estado_inicial,0,&visitados,&quantidade_visitados,&capacidade_visitados)) /*  o estado inicial ja apareceu na busca, entao guardamos ele */
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
    todos = registrar_no(todos, no_inicial);

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
            resultado.todos_nos = todos;
            free(visitados);
            return resultado;
        }

        // Adicionar estados seguintes na estrutura 
        SucessorCubo sucessores[TOTAL_MOVIMENTOS]; // cria o vetor que vai guardar os 12 sucessores gerados a partir do estado atual
        estado_gerar_sucessores(&atual->estado, sucessores); // chama a funcao sucessora que ja existe, e ela preenche o vetor sucessores

                
    for (int i = 0; i < TOTAL_MOVIMENTOS; i++) /* percorre cada um dos 12 sucessores gerados*/
    {

        int profundidade_filho = atual->profundidade + 1;
    
        if (deve_explorar(&sucessores[i].estado, profundidade_filho, &visitados, &quantidade_visitados, &capacidade_visitados)) /* verifica se esse estado ainda nao apareceu na busca */
        {
          
            NoBusca *filho = (NoBusca *)malloc(sizeof(NoBusca)); /* cria um novo no para representar esse sucessor */

            if (filho != NULL) /* verifica se conseguiu alocar memoria para o novo no */
            {
               filho->estado = sucessores[i].estado;
               filho->movimento = sucessores[i].movimento;
               filho->pai = atual;
               filho->profundidade = profundidade_filho;

              estrutura->inserir(estrutura->estrutura, filho); /* coloca o novo estado na estrutura da busca */
              todos = registrar_no(todos, filho);
            }
        }
    }

} // fecha o while

    // chegou aqui se a estrutura ficou vazia sem encontrar solucao
    resultado.todos_nos = todos;
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

void liberar_nos(ListaNos *lista)
{
    while (lista != NULL)
    {
        ListaNos *prox = lista->prox;
        free(lista->no);
        free(lista);
        lista = prox;
    }
}