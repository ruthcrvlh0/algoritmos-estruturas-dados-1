#include <stdio.h>
#include <stdlib.h>

int main() {
    int n_inimigos; 
    int *ponteiro_onda = NULL;
    
    printf("Digite a quantidade de inimigos da onda: \n");
    scanf("%d", &n_inimigos);
    
    if(n_inimigos == 0){
        printf("O valor de iimigos deve ser um valor positivo.");
        return 1;
    }
    
    ponteiro_onda = (int *) malloc(n_inimigos * sizeof(int));
    
    for(int i = 0; i < n_inimigos; i++){
        printf("Digite o ID do %d° Inimigo: ", i+1);
        scanf("%d", &ponteiro_onda[i]);
    }
    printf("Onda de inimigos criada com sucesso! IDs: ");
    for(int i = 0; i< n_inimigos; i++){
        printf("%d, ", ponteiro_onda[i]);
    }
    
    printf("\n");
    free(ponteiro_onda);
    ponteiro_onda = NULL;
    
    return 0;
}