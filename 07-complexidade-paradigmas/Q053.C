#include <stdio.h>

int main() {
    int energia;

    printf("--- Ritual de Diminuicao Arcana ---\n");

    printf("Digite o nivel de energia inicial do Golem (n): ");
    if (scanf("%d", &energia) != 1 || energia <= 1) {
        printf("A energia deve ser um numero inteiro maior que 1. Encerrando.\n");
        return 1;
    }

    printf("\n--- Pulsos do Ritual ---\n");

    while (energia > 1) {
        printf("Energia Atual: %d\n", energia);
        energia = energia / 2;
    }

    printf("Energia Final: %d. Ritual concluido.\n", energia);

    return 0;
}