#include "dijkstra.h"

/*Saber o menor caminho de uma cidade a outra e quantos quilometros foram percorridos*/
typedef struct cidade{
    char nome[50];
    int cep;
}Cidade;

void lerCidade(Cidade* city, int qtdCidades){
    for( int i = 0; i < qtdCidades; i++){
        printf("Digite o nome da cidade%d: ",i+1);
        scanf(" %[^\n]", city[i].nome);

        printf("cep: ");
        scanf("%d",&city[i].cep);
    }
}

int main(){
    int tamanhoGrafo,inicio, final, pesoTotal = 0, tamanhoCaminho = 0;
    int vertice1, vertice2, peso;   
    
    printf("Tamanho do grafo:  ");
    scanf("%d",&tamanhoGrafo);
   /*
    printf("Digite quantas cidades há para serem percorridas (elas devem ser até %d): ",tamanhoGrafo - 1);
    scanf("%d",&qtdCidades);

    while( qtdCidades > tamanhoGrafo - 1){
        printf("A quantidade de cidades excedeu o limite de vertices, tente novamente");

        scanf("%d",&qtdCidades);
    }
    */
    Grafo* grafo = criarGrafo(tamanhoGrafo + 1);
    Cidade citys[tamanhoGrafo];

    lerCidade(citys,tamanhoGrafo);


    for( int i = 0; i < tamanhoGrafo;i++){
        printf("Vertice%d: ",i+1);
        scanf("%d",&vertice1);
        printf("Vertice%d: ",i+2);
        scanf("%d",&vertice2);
        printf("Peso:");
        scanf("%d",&peso);

        if( vertice1 < 0 || vertice1 >= tamanhoGrafo || vertice2 < 0 || vertice2 >= tamanhoGrafo){
            printf("--- Erro: Vértices devem estar entre 0 e %d. Aresta ignorada. ---\n", tamanhoGrafo - 1);
        }else{
            adicionarAresta(grafo,vertice1,vertice2,peso,1);
        }
    }

    int *caminho;

    printf("Digite o inicio e o fim ( ex: 1 5): ");
    scanf("%d %d", &inicio, &final);

    // Validação de Início/Fim (Correção 1 e 4)
    if (inicio < 0 || inicio >= tamanhoGrafo || final < 0 || final >= tamanhoGrafo) {
        printf("Erro: Vértices de início e fim devem estar entre 0 e %d.\n", tamanhoGrafo - 1);
    } else {
        caminho = menorCaminho(grafo, inicio, final, &pesoTotal, &tamanhoCaminho);

        if (caminho != NULL) {
        printf("Rota Otimizada:\n");
        
        for (int i = 0; i < tamanhoCaminho; i++) {
                int idVertice = caminho[i]; // Pega o ID numérico (ex: 0)
                
                // ACESSA O DADO GENÉRICO USANDO O ID
                printf("%s ", citys[idVertice].nome); 
                printf("Cep: %d", citys[idVertice].cep); 
                
                if (i < tamanhoCaminho - 1) printf(" -> ");
            }
            printf("\nDistância total: %d km\n", pesoTotal);
    
            free(caminho);
        } else {
            printf("Não foi encontrado caminho entre %d e %d.\n", inicio, final);
        }
    }

    liberarGrafo(grafo);
    return 0;
}

