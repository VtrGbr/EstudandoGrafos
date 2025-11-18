#include "dijkstra.h"

/*Saber o menor caminho de uma cidade a outra e quantos quilometros foram percorridos*/

int main(){
    Grafo* grafo = criarGrafo();
    int qtdCidades,inicio, final, pesoTotal = 0, tamanhoCaminho = 0;
    int vertice1, vertice2, peso;   
    
    printf("Digite quantas cidades há para serem percorridas (elas devem ser até %d): ",MAX - 1);
    scanf("%d",&qtdCidades);

    while( qtdCidades > MAX - 1){
        printf("A quantidade de cidades excedeu o limite de vertices, tente novamente");

        scanf("%d",&qtdCidades);
    }

    for( int i = 0; i < qtdCidades;i++){
        printf("Vertice%d: ",i+1);
        scanf("%d",&vertice1);
        printf("Vertice%d: ",i+2);
        scanf("%d",&vertice2);
        printf("Peso:");
        scanf("%d",&peso);

        if( vertice1 < 0 || vertice1 >= MAX || vertice2 < 0 || vertice2 >= MAX){
            printf("--- Erro: Vértices devem estar entre 0 e %d. Aresta ignorada. ---\n", MAX - 1);
        }else{
            adicionarAresta(grafo,vertice1,vertice2,peso);
        }
    }

    int *caminho;

    printf("Digite o inicio e o fim ( ex: 1 5): ");
    scanf("%d %d", &inicio, &final);

    // Validação de Início/Fim (Correção 1 e 4)
    if (inicio < 0 || inicio >= MAX || final < 0 || final >= MAX) {
        printf("Erro: Vértices de início e fim devem estar entre 0 e %d.\n", MAX - 1);
    } else {
        caminho = menorCaminho(grafo, inicio, final, &pesoTotal, &tamanhoCaminho);

        if (caminho != NULL) {
            printf("Menor caminho: ");
            for (int i = 0; i < tamanhoCaminho; i++) {
                printf("%d", caminho[i]);
                if (i < tamanhoCaminho - 1) {
                    printf(" -> ");
                }
            }
            printf("\nQuilometros entre %d e %d = %d\n", inicio,final,pesoTotal);
            
            // IMPORTANTE: Liberar a memória alocada por menorCaminho
            free(caminho);
        } else {
            printf("Não foi encontrado caminho entre %d e %d.\n", inicio, final);
        }
    }


    return 0;
}

