#ifndef dijkstra_h
#define dijkstra_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//#define MAX 20 
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

Grafo* criarGrafo(int n);

//Adicionar relação entre os grafos 

void adicionarAresta(Grafo* grafo, int vertex1, int vertex2, int peso, int direcionado);
int encontrarMenorDistancia(int tamanhoGrafo,int dist[], int visitado[]);
ListaAdjacencia* criarListaAdjacencia(int valor);

int* menorCaminho(Grafo* grafo, int inicio,int destinoFinal,int *pesoTotal,int *tamanhoCaminho);

void liberarGrafo(Grafo* grafo);
#endif