#include "kruskal.h"


// --- Funções Auxiliares do Min-Heap ---

void swap(Aresta* a, Aresta* b) {
    Aresta temp = *a;
    *a = *b;
    *b = temp;
}

// Garante a propriedade do Min-Heap (Pai <= Filhos)
void minHeapify(MinHeap* heap, int index) {
    int menor = index;
    int esquerda = 2 * index + 1;
    int direita = 2 * index + 2;

    if (esquerda < heap->tamanho && heap->array[esquerda].peso < heap->array[menor].peso)
        menor = esquerda;

    if (direita < heap->tamanho && heap->array[direita].peso < heap->array[menor].peso)
        menor = direita;

    if (menor != index) {
        swap(&heap->array[menor], &heap->array[index]);
        minHeapify(heap, menor);
    }
}

// Extrai a aresta de menor peso (Raiz do Heap)
Aresta extracaoMin(MinHeap* heap) {
    // Se estiver vazio, retorna uma aresta inválida (peso -1 ou trata erro)
    Aresta vazia = {-1, -1, -1}; 
    if (heap->tamanho <= 0) return vazia;

    if (heap->tamanho == 1) {
        heap->tamanho--;
        return heap->array[0];
    }

    // Salva a raiz
    Aresta raiz = heap->array[0];
    // Move o último elemento para a raiz
    heap->array[0] = heap->array[heap->tamanho - 1];
    heap->tamanho--;
    // Reorganiza
    minHeapify(heap, 0);

    return raiz;
}

// Constroi o heap a partir de um array desordenado - O(E)
void contruirHeap(MinHeap* heap) {
    int n = heap->tamanho;
    // Começa do último nó não-folha e vai subindo
    for (int i = (n / 2) - 1; i >= 0; i--) {
        minHeapify(heap, i);
    }
}

//Função recursiva que acha quem eh o pai de um conjunto
int find(Unionfind* subsets,int i){
    if( subsets[i].pai != i){
        subsets[i].pai = find(subsets,subsets[i].pai);
    }

    return subsets[i].pai;
}

void subsetUnion(Unionfind* subsets, int x, int y){
    int raizX = find(subsets,x);
    int raizY = find(subsets,y);

    //Aqui uniremos a arvore menor sob a arvore maior
    if( subsets[raizX].rank < subsets[raizY].rank){
        subsets[raizX].pai = raizY;
    }else if( subsets[raizX].rank > subsets[raizY].rank){
        subsets[raizY].pai = raizX;
    }else{
        subsets[raizY].pai = raizX;
        subsets[raizX].rank++; 
    }

}

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


