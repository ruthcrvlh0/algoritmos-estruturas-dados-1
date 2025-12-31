#include <stdio.h>
#include <stdlib.h>
#include "heroi/heroi.h" 

int main() {
    int n_herois;
    Heroi *equipe = NULL; 

    printf("--- Montagem da Equipe Heroica ---\n");

    printf("Quantos heróis farão parte da equipe? (N): ");
    if (scanf("%d", &n_herois) != 1 || n_herois <= 0) {
        printf("Entrada inválida. Encerrando.\n");
        return 1;
    }

    equipe = aloca_roster(n_herois);
    if (equipe == NULL) {
        return 1; 
    }

    le_roster(equipe, n_herois);

    imprime_roster(equipe, n_herois);

    free(equipe);
    
    return 0;
}