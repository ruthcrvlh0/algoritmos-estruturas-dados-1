#include <stdio.h>
#include <stdlib.h>

#define LINHAS 5
#define COLUNAS 10

int main() {
    int *level_map = (int *) malloc(LINHAS * COLUNAS * sizeof(int));
    
    if(level_map == NULL){
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }
    
    for(int i = 0; i < LINHAS; i ++){
        for(int j = 0; j < COLUNAS; j++){
            int *celula = level_map + i * COLUNAS + j;
            
            if(i == LINHAS - 1){
                *celula = 1;
            }
            else{
                *celula = 0; 
            }
        }
    }
    
    printf("--- Mapa do Nível (0=Ar, 1=Chao) ---\n");
    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            printf("%d ", *(level_map + i * COLUNAS + j));
        }
        printf("\n");
    }
    
    free(level_map);
    level_map = NULL;
   
    return 0;
}