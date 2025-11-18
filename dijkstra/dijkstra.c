#include "dijkstra.h"

//Criar o grafico

Grafo* criarGrafo(int n){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = n;

    grafo->vertices = (ListaAdjacencia**)malloc(n * sizeof(ListaAdjacencia*));
    for( int i = 0; i <= n - 1; i++){
        grafo->vertices[i] = NULL;
        //grafo->visitado[i] = 0;
    }

    return grafo;
}

//Adicionar relação entre os grafos 

void adicionarAresta(Grafo* grafo, int vertex1, int vertex2, int peso, int direcionado){
    ListaAdjacencia* no1 = criarListaAdjacencia(vertex2);
    no1->peso = peso;
    no1->next = grafo->vertices[vertex1];
    grafo->vertices[vertex1] = no1;

    // Adiciona aresta de v2 para v1 (grafo não-direcionado)
    if( direcionado = 1){
        ListaAdjacencia* no2 = criarListaAdjacencia(vertex1);
        no2->peso = peso;
        no2->next = grafo->vertices[vertex2];
        grafo->vertices[vertex2] = no2;

    }

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

int encontrarMenorDistancia(int tamanhoGrafo,int dist[], int visitado[]) {
    int min = INT_MAX;
    int min_index = -1; // -1 indica que não encontrou

    for (int v = 0; v < tamanhoGrafo; v++) {
        if (visitado[v] == 0 && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}
//Menor caminho com peso (retornarei o array de inteiros do menor caminho)



int* menorCaminho(Grafo* grafo, int inicio, int destinoFinal, int* pesoTotal, int* tamanhoCaminho) {
    
    int tamanhoGrafo = grafo->numVertices;

    // 1. Estruturas de Dados do Algoritmo
    int dist[tamanhoGrafo];     // Armazena a menor distância de 'inicio' até 'i'
    int anterior[tamanhoGrafo]; // Armazena o nó anterior no caminho mais curto
    int visitado[tamanhoGrafo]; // Array local de visitados (não mexe no grafo)
    // 2. Inicialização
    for (int i = 0; i < tamanhoGrafo; i++) {
        dist[i] = INT_MAX;
        anterior[i] = -1; // -1 significa sem predecessor
        visitado[i] = 0;  // 0 significa não visitado
    }

    // A distância do início para ele mesmo é 0
    dist[inicio] = 0;

    // 3. Loop Principal do Dijkstra
    // Vamos iterar no máximo MAX-1 vezes
    for (int count = 0; count < tamanhoGrafo - 1; count++) {
        
        // Pega o vértice não visitado com menor distância
        int u = encontrarMenorDistancia(tamanhoGrafo,dist, visitado);

        // Se não achou (grafo desconexo) ou chegou no destino
        if (u == -1) {
            break;
        }

        // Marca como visitado
        visitado[u] = 1;

        // Se 'u' é o destino, podemos parar (otimização)
        if (u == destinoFinal) {
            break;
        }

        // 4. "Relaxamento" (Relaxation)
        // Itera sobre todos os vizinhos 'v' de 'u'
        ListaAdjacencia* v = grafo->vertices[u];
        while (v != NULL) {
            int vizinho = v->valor;
            int pesoAresta = v->peso;

            // Se o vizinho não foi visitado e
            // o caminho via 'u' é mais curto que o caminho atual...
            if (!visitado[vizinho] && dist[u] != INT_MAX && (dist[u] + pesoAresta < dist[vizinho])) {
                // Atualiza a distância
                dist[vizinho] = dist[u] + pesoAresta;
                // Registra que o caminho para 'vizinho' agora vem de 'u'
                anterior[vizinho] = u;
            }
            v = v->next;
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
    int* caminhoInvertido = (int*)malloc(tamanhoGrafo * sizeof(int));
    int i = 0;
    int atual = destinoFinal;

    while (atual != -1) {
        caminhoInvertido[i] = atual;
        i++;
        atual = anterior[atual];
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

    for (int i = 0; i < grafo->numVertices; i++) {
        ListaAdjacencia* atual = grafo->vertices[i];
        while (atual != NULL) {
            ListaAdjacencia* temp = atual;
            atual = atual->next;
            free(temp); // Libera cada nó da lista
        }
    }
    free(grafo); // Libera a struct principal do grafo
}
