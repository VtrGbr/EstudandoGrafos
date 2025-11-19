#ifndef dijkstra_h
#define dijkstra_h

#include "grafo.h"

//Função responsável por retornar qual vertice iremos analisar
int encontrarMenorDistancia(int tamanhoGrafo,int dist[], int visitado[]);

//Função principal. Retorna um vetor de interios com o menor caminho
int* menorCaminho(Grafo* grafo, int inicio,int destinoFinal,int *pesoTotal,int *tamanhoCaminho);

#endif