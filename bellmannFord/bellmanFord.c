#include "bellmanFord.h"


int* menorCaminho(Grafo* grafo, int inicio, int destinoFinal, int* pesoTotal, int* tamanhoCaminho) {
    int tamanhoGrafo = grafo->numVertices; 
    // 1. Estruturas de Dados do Algoritmo
    int dist[tamanhoGrafo];     // Armazena a menor distância de 'inicio' até 'i'
    int anterior[tamanhoGrafo]; // Armazena o nó anterior no caminho mais curto
    

    // 2. Inicialização
    for (int i = 0; i < tamanhoGrafo; i++) {
        dist[i] = INT_MAX;
        anterior[i] = -1; // -1 significa sem predecessor
        
    }

    // A distância do início para ele mesmo é 0
    dist[inicio] = 0;

    // 3. Loop Principal do Dijkstra
    // Vamos iterar no máximo MAX-1 vezes
    for (int i = 0; i <= tamanhoGrafo - 1; i++) {
        
        for( int u = 0; u < tamanhoGrafo; u++){
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
        for (int u = 0; u < tamanhoGrafo ;u++){
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
    int* caminhoInvertido = (int*)malloc(tamanhoGrafo * sizeof(int));
    int i = 0, count = 0;
    int atual = destinoFinal;

    while (atual != -1 && count < tamanhoGrafo) {
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

