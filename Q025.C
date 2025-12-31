#include <stdio.h>
#include<stdlib.h>

int main(){
    int n_inimigos;
    printf("Quantos inimigos tem essa fase? \n");
    scanf("%d", &n_inimigos);
    int *status_inimigos = (int *) calloc(n_inimigos, sizeof(int));
    
    printf("\nStatus Inicial (Inativo = 0\n");
    for (int i = 0; i < n_inimigos; i++) {
        printf("Inimigo %d: Inativo (%d)\n", i + 1, status_inimigos[i]);
    }
    
    for(int i = 0;i < n_inimigos; i++){
        if(status_inimigos[i] == 0){
            status_inimigos[i] = 1;
        }
    }
    
    printf("\nRelatorio Final (Ativo = 1)\n");
    for (int i = 0; i < n_inimigos; i++) {
        printf("Inimigo %d: Ativo (%d)\n", i + 1, status_inimigos[i]);
    }
    
    free(status_inimigos);
    status_inimigos = NULL;
    
    return 0;
}