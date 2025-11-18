#include "bellmanFord.h"

Grafo* criarGrafo(){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));

    for( int i = 0; i <= MAX - 1; i++){
        grafo->vertices[i] = NULL;
    }

    return grafo;
}

//Adicionar relação entre os grafos (grafo direcionado) 

void adicionarAresta(Grafo* grafo, int origem, int destino, int peso){
    ListaAdjacencia* no1 = criarListaAdjacencia(destino);
    no1->peso = peso;
    no1->next = grafo->vertices[origem];
    grafo->vertices[origem] = no1;

}


ListaAdjacencia* criarListaAdjacencia(int valor){
    ListaAdjacencia* lista = (ListaAdjacencia*)malloc(sizeof(ListaAdjacencia));

    if(lista == NULL){
        return NULL;
    }
    lista->valor = valor;
    lista->peso = 0;
    lista->next= NULL;

    return lista;
}


int* menorCaminho(Grafo* grafo, int inicio, int destinoFinal, int* pesoTotal, int* tamanhoCaminho) {
    
    // 1. Estruturas de Dados do Algoritmo
    int dist[MAX];     // Armazena a menor distância de 'inicio' até 'i'
    int anterior[MAX]; // Armazena o nó anterior no caminho mais curto
    

    // 2. Inicialização
    for (int i = 0; i < MAX; i++) {
        dist[i] = INT_MAX;
        anterior[i] = -1; // -1 significa sem predecessor
        
    }

    // A distância do início para ele mesmo é 0
    dist[inicio] = 0;

    // 3. Loop Principal do Dijkstra
    // Vamos iterar no máximo MAX-1 vezes
    for (int i = 0; i <= MAX - 1; i++) {
        
        for( int u = 0; u < MAX; u++){
            if(dist[u] == INT_MAX) continue;
            // 4. "Relaxamento" (Relaxation)
            // Itera sobre todos os vizinhos 'v' de 'u'
            ListaAdjacencia* v = grafo->vertices[u];
            while (v != NULL) {
                int vizinho = v->valor;
                int pesoAresta = v->peso;
    
                // Se o vizinho não foi visitado e
                // o caminho via 'u' é mais curto que o caminho atual...
                if (dist[u] != INT_MAX && (dist[u] + pesoAresta < dist[vizinho])) {
                    // Atualiza a distância
                    dist[vizinho] = dist[u] + pesoAresta;
                    // Registra que o caminho para 'vizinho' agora vem de 'u'
                    anterior[vizinho] = u;
                }
                v = v->next;
            }
        }
    }
        //Irei verificar se há ciclos negativos
        for (int u = 0; u < MAX ;u++){
            if( dist[u] == INT_MAX) continue;
    
            ListaAdjacencia* lista = grafo->vertices[u];
    
            while(lista != NULL){
                int vizinho = lista->valor;
                int pesoAresta = lista->peso;
    
    
                if( dist[u] != INT_MAX && (dist[vizinho] > dist[u] + pesoAresta)){
                    //ciclo negativo
                    printf("Ciclo negativo detectado.\n");
                    *pesoTotal= INT_MIN;
                    *tamanhoCaminho = 0;
                    
                    return NULL;
                    
                }
                lista = lista->next;
            }
        }



    // 5. Verificação e Reconstrução do Caminho

    // Se a distância até o destino ainda é INT_MAX, não há caminho
    if (dist[destinoFinal] == INT_MAX) {
        *pesoTotal = -1;
        *tamanhoCaminho = 0;
        return NULL; // Não há caminho
    }

    // O peso total é a distância calculada
    *pesoTotal = dist[destinoFinal];

    // Agora, vamos reconstruir o caminho usando o array 'anterior'
    // O caminho virá *invertido* (do destino para a origem)
    int* caminhoInvertido = (int*)malloc(MAX * sizeof(int));
    int i = 0, count = 0;
    int atual = destinoFinal;

    while (atual != -1 && count < MAX) {
        caminhoInvertido[i] = atual;
        i++;
        atual = anterior[atual];
        count++;
    }

    // 'i' agora é o número de nós no caminho
    *tamanhoCaminho = i;

    // Aloca o array final e o reverte para a ordem correta
    int* caminhoFinal = (int*)malloc((*tamanhoCaminho) * sizeof(int));
    for (int j = 0; j < *tamanhoCaminho; j++) {
        caminhoFinal[j] = caminhoInvertido[*tamanhoCaminho - 1 - j];
    }

    free(caminhoInvertido); // Libera o array temporário
    return caminhoFinal; // Retorna o caminho na ordem correta
}


void liberarGrafo(Grafo* grafo) {
    if (grafo == NULL) {
        return;
    }

    for (int i = 0; i < MAX; i++) {
        ListaAdjacencia* atual = grafo->vertices[i];
        while (atual != NULL) {
            ListaAdjacencia* temp = atual;
            atual = atual->next;
            free(temp); // Libera cada nó da lista
        }
    }
    free(grafo); // Libera a struct principal do grafo
}

int main(){
    // Variáveis 'menor' e 'maior' removidas por não serem necessárias
    // e por levarem a uma validação incorreta.
    int pesoTotal = 0, vertice1, vertice2, peso;
    int inicio, final;
    int tamanhoCaminho = 0;
    Grafo* grafo = criarGrafo();
    int* caminho;
    char entrada = 'u';

    while (entrada != 'p' && entrada != 'P') {
        
        // Validação de Vértices (Correção 1)
        printf("Digite o vertice 1 (entre 0 e %d): ", MAX - 1);
        scanf("%d", &vertice1);
        printf("Digite o vertice 2 (entre 0 e %d): ", MAX - 1);
        scanf("%d", &vertice2);

        // Garante que os vértices estão DENTRO dos limites do array
        if (vertice1 < 0 || vertice1 >= MAX || vertice2 < 0 || vertice2 >= MAX) {
            printf("--- Erro: Vértices devem estar entre 0 e %d. Aresta ignorada. ---\n", MAX - 1);
        } else {
            printf("Digite o peso: ");
            scanf("%d", &peso);
            adicionarAresta(grafo, vertice1, vertice2, peso);
        }

        printf("Continuar? (Digite 'p' para parar, outra tecla para continuar): ");
        scanf(" %c", &entrada); // O espaço antes de %c é crucial
    }

    printf("Digite o inicio e o fim ( ex: 1 5): ");
    scanf("%d %d", &inicio, &final);

    // Validação de Início/Fim (Correção 1 e 4)
    if (inicio < 0 || inicio >= MAX || final < 0 || final >= MAX) {
        printf("Erro: Vértices de início e fim devem estar entre 0 e %d.\n", MAX - 1);
    } else {
        caminho = menorCaminho(grafo, inicio, final, &pesoTotal, &tamanhoCaminho);

        if (caminho != NULL) {
            printf("Menor caminho: ");
            for (int i = 0; i < tamanhoCaminho; i++) {
                printf("%d", caminho[i]);
                if (i < tamanhoCaminho - 1) {
                    printf(" -> ");
                }
            }
            printf("\nPeso total = %d\n", pesoTotal);
            
            // IMPORTANTE: Liberar a memória alocada por menorCaminho
            free(caminho);
        } else {
            printf("Não foi encontrado caminho entre %d e %d.\n", inicio, final);
        }
    }

    // Liberação de memória (Correção 3)
    // Deve estar fora do if/else para ser executada sempre.
    liberarGrafo(grafo);

    return 0;
}