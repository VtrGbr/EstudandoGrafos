#ifndef grafo_h
#define grafo_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct listaAdjacencia{
    int valor;
    int peso;
    struct listaAdjacencia* next;
}ListaAdjacencia;

typedef struct grafo{
    ListaAdjacencia **vertices;
    int numVertices;
    //int visitado[MAX];
}Grafo;

typedef struct aresta{
    int origem;
    int destino;
    int peso;
}Aresta;

typedef struct unionfind{
    int pai;
    int rank;
}Unionfind;

Grafo* criarGrafo(int n);

//Adicionar relação entre os grafos 

void adicionarAresta(Grafo* grafo, int vertex1, int vertex2, int peso, int direcionado);

ListaAdjacencia* criarListaAdjacencia(int valor);

void liberarGrafo(Grafo* grafo);

#endif 