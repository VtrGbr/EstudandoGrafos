#ifndef kruskal_h
#define kruskal_h

#include "grafo.h"

//Estrutura para a min-heap
typedef struct minHeap{
    Aresta * array;
    int tamanho;
    int capacidade;
}MinHeap;

void swap(Aresta* a, Aresta* b);

// Garante a propriedade do Min-Heap (Pai <= Filhos)
void minHeapify(MinHeap* heap, int index);
// Extrai a aresta de menor peso (Raiz do Heap)
Aresta extracaoMin(MinHeap* heap);

// Constroi o heap a partir de um array desordenado - O(E)
void contruirHeap(MinHeap* heap);

//Subsets: Vetor que contem o valor do pai de um número e o rank dele
//i: Variavel que usaremos para ir vasculhando o vetor subsets
//Esta eh uma função recursiva. Use ela para encontrar o pai de um conjunto
int find(Unionfind* subsets, int i);

//Esta funcao une dois conjuntos 
void subsetUnion(Unionfind* subsets, int x, int y);

//Funcao principal que gera a arvore mst
void kruskalMST(Grafo* grafo);

#endif