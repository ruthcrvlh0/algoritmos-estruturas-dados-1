#include <stdio.h>
#include <stdlib.h>

int main() {
    int linhas, colunas;
    int **mapa = NULL; 
    int contador_tijolos = 0;
        
    printf("Digite o numero de linhas e colunas do mapa (ex: 5 10): ");

    if (scanf("%d %d", &linhas, &colunas) != 2 || linhas <= 0 || colunas <= 0) {
        printf("Erro: Dimensoes invalidas ou leitura incorreta.\n");
        return 1;
    }

    mapa = (int **) malloc(linhas * sizeof(int *));

    if (mapa == NULL) {
        printf("Erro: Falha ao alocar memoria para as linhas.\n");
        return 1;
    }

    for (int i = 0; i < linhas; i++) {
        mapa[i] = (int *)malloc(colunas * sizeof(int));
        
        // BOAS PRÁTICAS
        if (mapa[i] == NULL) {
            printf("Erro: Falha ao alocar memoria para a linha %d.\n", i);
            
            for (int k = 0; k < i; k++) {
                free(mapa[k]);
            }
            free(mapa);
            return 1;
        }
    }
            
    printf("Digite o valor para cada celula (0=Ar, 1=Tijolo, 2=Agua): \n");
        
    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            printf("Mapa[%d][%d]: ", i, j);
            scanf("%d", &mapa[i][j]);
        }
    }

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(mapa[i][j] == 1){
                contador_tijolos++;
            }
        }
    }

    printf("\nO mapa possui %d blocos de tijolo.\n", contador_tijolos);

    for(int i = 0; i < linhas; i++){
        free(mapa[i]); 
    }
        
    free(mapa); 
    mapa = NULL;
        
    return 0;
}