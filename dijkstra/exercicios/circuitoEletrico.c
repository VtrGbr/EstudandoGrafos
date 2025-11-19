#include "dijkstra.h"

typedef struct circuito{
    //double resistencia; // Referente ao peso
    char noh;
    int tamanho; // So para saber qual o tamanho do vetor
}Circuito;

int circuitoVertice(Circuito* circuito,char noh){
    for( int i = 0; i < circuito->tamanho;i++){
        if( circuito[i].noh == noh){
            return i;
        }
    }

    return -1;
}

void lerCircuito(Circuito* circle,int numeroNohs){
    for(int i = 0; i < numeroNohs; i++){
        printf("Noh: ");
        scanf(" %c",&circle[i].noh);
        /*printf("Resistencia: ");
        scanf("%lf",&circle[i].resistencia);*/
    }
    circle->tamanho = numeroNohs;
}

int main(){
    int numNohs, numArestas;
    int inicio, final, pesoTotal = 0, tamanhoCaminho = 0;
    int vertice1, vertice2, peso;
    char nohA, nohB;   
    
    printf("Quantidade de cidades (vertices): ");
    scanf("%d", &numNohs);

    // Cria o grafo com o tamanho exato
    Grafo* grafo = criarGrafo(numNohs);
    Circuito circle[numNohs];

    lerCircuito(circle, numNohs);

    //Perguntar quantas estradas existem separadamente
    printf("\nQuantas conexoes existem no circuito ");
    scanf("%d", &numArestas);

    for( int i = 0; i < numArestas; i++){
        printf("\n--- Conexão %d ---\n", i+1);
        printf("Ponto de origem: ");
        scanf(" %c", &nohA);
        
        printf("Ponto de destino: ");
        scanf(" %c", &nohB);
        
        printf("Resitencia entre os nohs (ohm): ");
        scanf("%d", &peso);

        vertice1 = circuitoVertice(circle, nohA);
        vertice2 = circuitoVertice(circle, nohB);

        if( vertice1 == -1 || vertice2 == -1){
            printf("Erro: Um dos pontos não foi encontrado. Tente novamente.\n");
            i--; // Decrementa para repetir a iteração
        } else {
            adicionarAresta(grafo, vertice1, vertice2, peso, 1);
        }
    }

    int *caminho;

    // CORREÇÃO 2: Ler nomes em vez de índices numéricos
    printf("\n--- Calcular menor camaninho da corrente elétrica ---\n");
    printf("Digite o nome do noh de INICIO: ");
    scanf(" %c", &nohA);
    
    printf("Digite o nome da cidade de DESTINO: ");
    scanf(" %c", &nohB);

    inicio = circuitoVertice(circle, nohA);
    final = circuitoVertice(circle, nohB);

    if (inicio == -1 || final == -1) {
        printf("Erro: Nohs de início ou fim inválidas.\n");
    } else {
        caminho = menorCaminho(grafo, inicio, final, &pesoTotal, &tamanhoCaminho);

        if (caminho != NULL) {
            printf("\n=== Rota Otimizada ===\n");
            
            for (int i = 0; i < tamanhoCaminho; i++) {
                int idVertice = caminho[i];
                
                printf("%c", circle[idVertice].noh);
                
                if (i < tamanhoCaminho - 1) printf(" -> ");
            }
            printf("\n\nResistencia total do caminho: %d ohm\n", pesoTotal);
            free(caminho);
        } else {
            printf("\nNão existe caminho possível entre %c e %c.\n", nohA, nohB);
        }
    }

    liberarGrafo(grafo);
    return 0;
}