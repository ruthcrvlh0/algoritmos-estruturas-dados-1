#include <stdio.h>

/**
 * @brief Calcula o dano bônus do Golpe Ecoante de forma recursiva.
 * * @param n O número do golpe na sequência (N >= 1).
 * @return O dano bônus correspondente ao golpe N.
 */
int calcularDanoEco(int n) {

    if (n == 1) {
        return 0;
    }

    if (n == 2) {
        return 1;
    }

    return calcularDanoEco(n - 1) + calcularDanoEco(n - 2);
}

int main() {
    int N;
    int dano_bonus;

    printf("--- Calculo de Dano Bonus do Golpe Ecoante ---\n");

    printf("Digite o numero do golpe na sequencia (N >= 1): ");
    if (scanf("%d", &N) != 1 || N < 1) {
        printf("Entrada invalida. O numero do golpe deve ser um inteiro positivo.\n");
        return 1;
    }

    dano_bonus = calcularDanoEco(N);
    printf("\nO dano bonus do %do golpe e: %d pontos.\n", N, dano_bonus);

    return 0;
}