#include "grafo.h"

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
