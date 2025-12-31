#include <stdio.h>
#include <stdlib.h>

int main() {
    void * ponteiro_duracao = malloc(sizeof(int));
    (*(int*)ponteiro_duracao) = 10;
    printf("Power-up 'Super Salto' ativado! Duracao: %d segundos.\n", *((int *)ponteiro_duracao));
    
    (*(int*)ponteiro_duracao) = 10 - 3;
    
    printf("3 segundos se passaram... Duracao restante: %d segundos.\n", *((int *)ponteiro_duracao));
      
    free(ponteiro_duracao);
    ponteiro_duracao = NULL;
    
    return 0;
}