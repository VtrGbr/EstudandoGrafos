#include "dijkstra.h"
#include <string.h>


typedef struct cidade{
    char nome[50];
    int populacao; 
} Cidade;

void lerCidade(Cidade* city, int qtdCidades){
    for( int i = 0; i < qtdCidades; i++){
        printf("\n--- Cadastro da Cidade %d ---\n", i);
        printf("Nome: ");
        
        scanf(" %[^\n]", city[i].nome);

        printf("População: "); 
        scanf("%d", &city[i].populacao);
    }
}

int verticeCidade(Cidade* city, char* nomeCidade, int tamanhoCidade){
    for( int i = 0; i < tamanhoCidade; i++){
        if(strcmp(city[i].nome, nomeCidade) == 0){
            return i;
        }
    }
    return -1;
}

int main(){
    int numCidades, numArestas;
    int inicio, final, pesoTotal = 0, tamanhoCaminho = 0;
    int vertice1, vertice2, peso;
    char nomeCidadeA[50], nomeCidadeB[50];   
    
    printf("Quantidade de cidades (vertices): ");
    scanf("%d", &numCidades);

    // Cria o grafo com o tamanho exato
    Grafo* grafo = criarGrafo(numCidades);
    Cidade citys[numCidades];

    lerCidade(citys, numCidades);

    //Perguntar quantas estradas existem separadamente
    printf("\nQuantas estradas (conexoes) existem entre as cidades? ");
    scanf("%d", &numArestas);

    for( int i = 0; i < numArestas; i++){
        printf("\n--- Conexão %d ---\n", i+1);
        printf("Cidade de Origem: ");
        scanf(" %[^\n]", nomeCidadeA);
        
        printf("Cidade de Destino: ");
        scanf(" %[^\n]", nomeCidadeB);
        
        printf("Distância (Peso em Km): ");
        scanf("%d", &peso);

        vertice1 = verticeCidade(citys, nomeCidadeA, numCidades);
        vertice2 = verticeCidade(citys, nomeCidadeB, numCidades);

        if( vertice1 == -1 || vertice2 == -1){
            printf("Erro: Uma das cidades não foi encontrada. Tente novamente.\n");
            i--; // Decrementa para repetir a iteração
        } else {
            adicionarAresta(grafo, vertice1, vertice2, peso, 0);
        }
    }

    int *caminho;

    // CORREÇÃO 2: Ler nomes em vez de índices numéricos
    printf("\n--- Calcular Rota ---\n");
    printf("Digite o nome da cidade de INICIO: ");
    scanf(" %[^\n]", nomeCidadeA);
    
    printf("Digite o nome da cidade de DESTINO: ");
    scanf(" %[^\n]", nomeCidadeB);

    inicio = verticeCidade(citys, nomeCidadeA, numCidades);
    final = verticeCidade(citys, nomeCidadeB, numCidades);

    if (inicio == -1 || final == -1) {
        printf("Erro: Cidades de início ou fim inválidas.\n");
    } else {
        caminho = menorCaminho(grafo, inicio, final, &pesoTotal, &tamanhoCaminho);

        if (caminho != NULL) {
            printf("\n=== Rota Otimizada ===\n");
            
            for (int i = 0; i < tamanhoCaminho; i++) {
                int idVertice = caminho[i];
                
                printf("%s (Pop: %d)", citys[idVertice].nome, citys[idVertice].populacao);
                
                if (i < tamanhoCaminho - 1) printf(" -> ");
            }
            printf("\n\nDistância total: %d km\n", pesoTotal);
            free(caminho);
        } else {
            printf("\nNão existe caminho possível entre %s e %s.\n", nomeCidadeA, nomeCidadeB);
        }
    }

    liberarGrafo(grafo);
    return 0;
}