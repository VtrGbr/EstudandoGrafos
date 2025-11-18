#ifndef bellmanFord_h
#define bellmanFord_h

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 7

typedef struct listaAdjacencia{
    int valor;
    int peso;
    struct listaAdjacencia* next;
}ListaAdjacencia;

typedef struct grafo{
    ListaAdjacencia* vertices[MAX];
}Grafo;

Grafo* criarGrafo();

//Adicionar relação entre os grafos (grafo direcionado) 

void adicionarAresta(Grafo* grafo, int origem, int destino, int peso);


ListaAdjacencia* criarListaAdjacencia(int valor);

int* menorCaminho(Grafo* grafo, int inicio, int destinoFinal, int* pesoTotal, int* tamanhoCaminho);


void liberarGrafo(Grafo* grafo);

#endif