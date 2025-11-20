# Objetivo:
-   Este repositório tem como objetivo estudar os algoritmos de teoria dos grafos

## Algoritmos que pretendo abordar no estudo

1. Dijkstra;
2. Floyd;
3. bellmann-ford;
4. Kruskal;
5. Prim;

### Linguagem utilizada:
Utilizarei a linguagem C para realizar o estudo e exercícios desses algorítmos.

# Como rodar:

1. Dijkstra:
- Objetivo: Descobrir o menor caminho entre um grafo ponderado. Aceita pesos não negativos

- Como rodar: 
1.1. Abra a pasta **dijkstra** e no terminal execute este comando:

```bash
    gcc dijkstra.c dijkstra.h -o "nomeExecutavel" 
```
1.2. Trecho do código:

```C
    int encontrarMenorDistancia(int dist[], int visitado[]) {
        int min = INT_MAX;
        int min_index = -1; // -1 indica que não encontrou

        for (int v = 0; v < MAX; v++) {
            if (visitado[v] == 0 && dist[v] < min) {
                min = dist[v];
                min_index = v;
            }
        }
        return min_index;
    }
```

- MenorCaminho:
```C
// 3. Loop Principal do Dijkstra
    // Vamos iterar no máximo MAX-1 vezes
    for (int count = 0; count < MAX - 1; count++) {
        
        // Pega o vértice não visitado com menor distância
        int u = encontrarMenorDistancia(dist, visitado);

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

```
- Exercícios:
    Nesta pasta contém alguns exercícios simples sobre cada grafo da pasta.
    Para roda-los, digite este comando no 

1. Cidade Viável: Neste exercício o objetivo é encontrar o menor caminho de uma cidade até outra
Como rodar: 
```bash
    gcc cidadeViavel.c ../dijkstra.c ../../grafo.c -I../ -I../../ -o "nomeExecutavel"
```

2. Circuito elétrico: O objetivo é encontrar o menor caminho que uma corrente elétrica percorre em um circuito:
Como rodar:

```bash
    gcc circuitoEletrico.c ../dijkstra.c ../../grafo.c -I../ -I../../ -o "nomeExecutavel"
```

2. Bellman-Ford:

- Objetivo: Encontrar o menor caminho entre um grafo ponderado. Entretando ele aceita pesos negativos. Quando encontra um ciclo negativo ele para, pois isso pode alterar o valor das distâncias de cada vértice e o programa pode rodar mais tempo que o necessário.

- Como rodar:

2.1. Abra a pasta **bellmanFord** e no terminal execute este comando:

```bash
    gcc bellmanFord.c bellmanFord.h -o "nomeExecutavel"
```

2.2. Trecho do Código: Contido na função **menorCaminho**

```C
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
```

3. Kruskal:

- Objetivo: Gerar uma árvore de custo mínimo. O algoritmo usa uma fila de prioridade (min-heap) para ordernar as arestas. Para otimizar a união dos conjutos, usa-se o algoritmo Union find, para poder fazer a **Union By rank**.

- Trechos do código:
**Função principal**
```C
void kruskalMST(Grafo* grafo) {
    // 1. Coletar todas as arestas do grafo
    // Alocamos espaço para MAX*MAX arestas (pior caso grafo completo)
    int tamanhoGrafo = grafo->numVertices;
    int maxArestas = tamanhoGrafo * tamanhoGrafo; 
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->array = (Aresta*)malloc(maxArestas * sizeof(Aresta));
    heap->tamanho = 0;
    heap->capacidade = maxArestas;

    // Varre a Lista de Adjacência para preencher o array do Heap
    for (int u = 0; u < tamanhoGrafo; u++) {
        ListaAdjacencia* temp = grafo->vertices[u];
        while (temp != NULL) {
            int valor = temp->valor;
            int peso = temp->peso;
            
            // Evitar duplicatas em grafo não direcionado (u->v e v->u)
            if (u < valor) {
                heap->array[heap->tamanho].origem = u;
                heap->array[heap->tamanho].destino = valor;
                heap->array[heap->tamanho].peso = peso;
                heap->tamanho++;
            }
            temp = temp->next;
        }
    }

    // 2. Transformar o array em Heap (Build Heap) - Eficiência O(E)
    buildMinHeap(heap);

    // 3. Preparar Union-Find
    Unionfind* subsets = (Unionfind*)malloc(tamanhoGrafo * sizeof(Unionfind));
    for (int v = 0; v < tamanhoGrafo; v++) {
        subsets[v].pai = v;
        subsets[v].rank = 0;
    }

    Aresta* mst = (Aresta*)malloc(tamanhoGrafo * sizeof(Aresta));
    int arestasMST = 0;
    int custoTotal = 0;

    printf("--- Processando Kruskal com Min-Heap ---\n");

    // 4. Loop Principal: Enquanto houver arestas e a MST não estiver completa
    while (heap->tamanho > 0 && arestasMST < tamanhoGrafo - 1) {
        // Pega a menor aresta (O(log E))
        Aresta arestaAtual = extracaoMin(heap);

        int x = find(subsets, arestaAtual.origem);
        int y = find(subsets, arestaAtual.destino);

        // Se não forma ciclo (estão em conjuntos diferentes)
        if (x != y) {
            mst[arestasMST++] = arestaAtual;
            custoTotal += arestaAtual.peso;
            unionSets(subsets, x, y);
            printf("Aresta adicionada: %d -- %d (Peso: %d)\n", 
                   arestaAtual.origem, arestaAtual.destino, arestaAtual.peso);
        }
    }

    printf("\nCusto Total da MST: %d\n", custoTotal);

    // Limpeza de memória
    free(heap->array);
    free(heap);
    free(subsets);
    free(mst);
}

```

