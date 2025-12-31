#include <stdio.h>
#include <stdlib.h>

//complementar
#include <unistd.h>

int main() {
    int *duracao_fumaca = (int *) malloc(sizeof(int));
    
    if (duracao_fumaca == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }
    
    *duracao_fumaca = 5;
    printf("Bomba de fumaca ativada! Duracao: %d segundos\n", *duracao_fumaca);
    
    //complementar
    printf("Aguardando %d segundos...\n", *duracao_fumaca);
    sleep(*duracao_fumaca);
    
    free(duracao_fumaca);
    duracao_fumaca = NULL;
    printf("A fumaca se dissipou.\n");
      
    return 0;
}